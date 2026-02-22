#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* WIFI */
const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";

/* LCD */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* PINS */
#define GAS_SENSOR A0
#define LED_PIN D5
#define BUZZER_PIN D6

/* VARIABLES */
int baseline = 0;
int margin = 60;
int gasValue = 0;

bool systemEnabled = true;
bool ledEnabled = true;
bool buzzerEnabled = true;

/* BUZZER TIMER */
unsigned long buzzerTimer = 0;
bool buzzerState = false;
const unsigned long buzzerInterval = 500; // ms

ESP8266WebServer server(80);

/* ---------- DASHBOARD ---------- */
void handleRoot() {
  bool gasAlert = (gasValue > baseline + margin) && systemEnabled;

  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="refresh" content="1">
<title>Gas Safety System</title>

<style>
body{
  margin:0;
  font-family:Arial,Segoe UI;
  background:#020617;
  color:white;
}
.wrapper{
  max-width:480px;
  margin:auto;
  padding:30px 20px;
}
.title{
  text-align:center;
  font-size:28px;
  font-weight:700;
  letter-spacing:2px;
  margin-bottom:30px;
}
.card{
  background:#0f172a;
  border-radius:20px;
  padding:22px;
  margin-bottom:22px;
  box-shadow:0 10px 30px rgba(0,0,0,0.5);
}
.status{
  text-align:center;
  font-size:22px;
  font-weight:700;
  padding:16px;
  border-radius:16px;
}
.safe{background:#15803d;}
.alert{background:#b91c1c;}
.value{
  text-align:center;
  font-size:40px;
  font-weight:700;
}
.subtitle{
  text-align:center;
  opacity:0.7;
  margin-top:8px;
}
.controls{
  display:grid;
  grid-template-columns:1fr 1fr;
  gap:16px;
  margin-top:10px;
}
button{
  padding:18px;
  font-size:16px;
  font-weight:700;
  border:none;
  border-radius:16px;
  cursor:pointer;
  transition:0.2s;
}
button:active{transform:scale(0.95);}
.on{background:#22c55e;color:black;}
.off{background:#ef4444;color:white;}
.full{grid-column:span 2;}
.footer{
  text-align:center;
  font-size:12px;
  opacity:0.6;
  margin-top:10px;
}
</style>
</head>

<body>
<div class="wrapper">

<div class="title">GAS SAFETY SYSTEM</div>

<div class="card">
<div class="status )rawliteral";

  page += gasAlert ? "alert\">!GAS DETECTED!" : "safe\">SAFE";
  page += R"rawliteral(
</div>
</div>

<div class="card">
<div class="value">)rawliteral";
  page += gasValue;
  page += R"rawliteral(</div>
<div class="subtitle">Gas Sensor Value</div>
</div>

<div class="card">
<h3 style="text-align:center;margin-bottom:15px;">Manual Controls</h3>
<div class="controls">

<a href="/toggleSystem">
<button class="full )rawliteral";
  page += systemEnabled ? "on\">SYSTEM ON" : "off\">SYSTEM OFF";
  page += R"rawliteral(</button></a>

<a href="/toggleLED">
<button class=")rawliteral";
  page += ledEnabled ? "on\">LED ON" : "off\">LED OFF";
  page += R"rawliteral(</button></a>

<a href="/toggleBuzzer">
<button class=")rawliteral";
  page += buzzerEnabled ? "on\">BUZZER ON" : "off\">BUZZER OFF";
  page += R"rawliteral(</button></a>

</div>
</div>

<div class="footer">ESP8266 Smart Gas Safety Dashboard</div>

</div>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

/* ---------- TOGGLES ---------- */
void toggleSystem() {
  systemEnabled = !systemEnabled;
  server.sendHeader("Location", "/");
  server.send(303);
}
void toggleLED() {
  ledEnabled = !ledEnabled;
  server.sendHeader("Location", "/");
  server.send(303);
}
void toggleBuzzer() {
  buzzerEnabled = !buzzerEnabled;
  buzzerState = false;
  digitalWrite(BUZZER_PIN, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

/* ---------- SETUP ---------- */
void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  lcd.clear();
  lcd.print("IP Address:");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  delay(3000);

  long sum = 0;
  for(int i=0;i<30;i++){
    sum += analogRead(GAS_SENSOR);
    delay(100);
  }
  baseline = sum / 30;

  lcd.clear();
  lcd.print("System Ready");

  server.on("/", handleRoot);
  server.on("/toggleSystem", toggleSystem);
  server.on("/toggleLED", toggleLED);
  server.on("/toggleBuzzer", toggleBuzzer);
  server.begin();
}

/* ---------- LOOP ---------- */
void loop() {
  server.handleClient();

  gasValue = analogRead(GAS_SENSOR);
  bool gasAlert = (gasValue > baseline + margin) && systemEnabled;

  /* LED CONTROL */
  digitalWrite(LED_PIN, (gasAlert && ledEnabled) ? HIGH : LOW);

  /* BUZZER INTERMITTENT CONTROL */
  if (gasAlert && buzzerEnabled) {
    if (millis() - buzzerTimer >= buzzerInterval) {
      buzzerTimer = millis();
      buzzerState = !buzzerState;
      digitalWrite(BUZZER_PIN, buzzerState);
    }
  } else {
    buzzerState = false;
    digitalWrite(BUZZER_PIN, LOW);
  }

  /* LCD */
  lcd.setCursor(0,0);
  if (gasAlert) lcd.print("GAS DETECTED!  ");
  else lcd.print("SAFE ALERT     ");

  lcd.setCursor(0,1);
  lcd.print("Gas:");
  lcd.print(gasValue);
  lcd.print("   ");
}
