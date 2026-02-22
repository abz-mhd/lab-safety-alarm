# 🚨 Lab Safety Alarm

<div align="center">

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![ESP8266](https://img.shields.io/badge/ESP8266-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Firebase](https://img.shields.io/badge/Firebase-FFCA28?style=for-the-badge&logo=firebase&logoColor=black)

[![GitHub stars](https://img.shields.io/github/stars/abz-mhd/lab-safety-alarm?style=for-the-badge)](https://github.com/abz-mhd/lab-safety-alarm/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/abz-mhd/lab-safety-alarm?style=for-the-badge)](https://github.com/abz-mhd/lab-safety-alarm/network)
[![GitHub issues](https://img.shields.io/github/issues/abz-mhd/lab-safety-alarm?style=for-the-badge)](https://github.com/abz-mhd/lab-safety-alarm/issues)
[![GitHub license](https://img.shields.io/github/license/abz-mhd/lab-safety-alarm?style=for-the-badge)](LICENSE) <!-- TODO: Add LICENSE file if applicable -->

**An ESP32-based IoT system for real-time laboratory environment monitoring, hazard detection, and automated safety responses.**

</div>

## 📖 Overview

This project implements an intelligent lab safety alarm system using an ESP32 microcontroller. It continuously monitors crucial environmental parameters such as temperature, humidity, gas concentration, and flame presence. Upon detecting hazardous conditions that exceed predefined thresholds, the system automatically triggers an alarm, activates ventilation (fan), controls a window (servo motor), and provides visual feedback via LEDs and an I2C LCD. All sensor data and alarm statuses are logged and can be monitored remotely via Firebase Realtime Database, making it an ideal solution for ensuring safety in laboratory environments.

## ✨ Features

-   **Real-time Environmental Monitoring:** Tracks temperature, humidity, combustible gas levels (MQ series), and flame detection.
-   **Automated Hazard Response:**
    -   **Audible Alarm:** Activates a buzzer upon detection of critical hazards (high gas, flame, extreme temperature/humidity).
    -   **Visual Indicators:** Red, Yellow, and Green LEDs provide immediate visual cues for danger, warning, or safe states.
    -   **Automatic Ventilation:** Controls a DC fan based on high temperature or gas concentration to improve air quality.
    -   **Automatic Window Control:** Utilizes a servo motor to open/close a window (simulated) in response to detected hazards.
-   **Data Logging & Remote Monitoring:** Integrates with Firebase Realtime Database to store and provide remote access to all sensor readings and system statuses.
-   **Local Data Display:** An I2C LCD provides real-time display of current sensor values, time, and system alerts directly in the lab.
-   **Manual Override:** A push button allows for manual activation or deactivation of the alarm system.
-   **Time Synchronization:** Uses NTP (Network Time Protocol) to ensure accurate timekeeping for display and data logging.
-   **Wi-Fi Connectivity:** Enables seamless communication with Firebase and NTP servers.

## 🛠️ Tech Stack

**Microcontroller:**
![ESP8266](https://img.shields.io/badge/ESP8266-E7352C?style=for-the-badge&logo=espressif&logoColor=white)

**Programming Language:**
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

**Development Platform:**
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)

**Cloud & Database:**
![Google Firebase](https://img.shields.io/badge/Google_Firebase-FFCA28?style=for-the-badge&logo=firebase&logoColor=black)

**Libraries:**
-   **Wire.h:** I2C communication.
-   **LiquidCrystal_I2C.h:** For I2C LCD display.
-   **DHT.h:** For DHT11/22 temperature/humidity sensor.
-   **FirebaseESP32.h:** For Firebase integration.
-   **ESP32Servo.h:** For servo motor control.
-   **WiFi.h, HTTPClient.h, NTPClient.h:** For network connectivity and time synchronization.

## 🎛️ Hardware Components

To build this project, you will need the following hardware components:

-   **ESP32 Development Board:** The central processing unit for the system.
-   **DHT11/DHT22 Sensor:** For temperature and humidity measurement.
-   **MQ-series Gas Sensor (e.g., MQ-2, MQ-3, MQ-7):** For detecting combustible gas concentrations.
-   **Flame Sensor:** For detecting the presence of fire.
-   **I2C LCD (16x2 or 20x4):** To display real-time sensor data and system status.
-   **Buzzer:** For audible alarm alerts.
-   **DC Fan:** For ventilation control.
-   **Servo Motor:** To simulate automatic window opening/closing.
-   **LEDs (Red, Yellow, Green):** For visual status indicators.
-   **Push Button:** For manual alarm control.
-   **Jumper Wires:** For connecting components.
-   **Breadboard:** For prototyping (optional).
-   **Resistors:** As required by LEDs and sensors.

## 🚀 Setup & Installation

Follow these steps to set up and run the Lab Safety Alarm system:

### Prerequisites

1.  **Arduino IDE:** Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2.  **ESP32 Board Manager:**
    *   Open Arduino IDE and go to `File > Preferences`.
    *   In "Additional Board Manager URLs", add: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
    *   Go to `Tools > Board > Board Manager`, search for "esp32", and install the "esp32 by Espressif Systems" package.
    *   Select your ESP32 board from `Tools > Board > ESP32 Arduino`.

### Library Installation

Install the following libraries using the Arduino IDE's Library Manager (`Sketch > Include Library > Manage Libraries...`):

-   **LiquidCrystal I2C:** Search for `LiquidCrystal I2C` and install the one by `Frank de Brabander`.
-   **DHT sensor library:** Search for `DHT sensor library` and install the one by `Adafruit`.
-   **Firebase ESP32 Client:** Search for `Firebase ESP32 Client` and install the one by `mobizt`.
-   **ESP32Servo:** Search for `ESP32Servo` and install the one by `Kevin Harrington`.
-   **NTPClient:** Search for `NTPClient` and install the one by `Fabrice Weinberg`.

### Firebase Project Setup

1.  **Create a Firebase Project:** Go to the [Firebase Console](https://console.firebase.google.com/) and create a new project.
2.  **Enable Realtime Database:** In your project, navigate to "Realtime Database" and create a new database.
3.  **Authentication:** Go to "Project settings" (the gear icon next to "Project Overview").
    *   Note your **Web API Key**.
    *   Go to "Service accounts" and generate a **new private key** for your ESP32. This will download a JSON file. Extract the `private_key_id` and `private_key` from it. *For simpler projects, you can use the Legacy server key from `Project settings > Cloud Messaging`, but the private key method is more secure.*
4.  **Database Rules:** For initial testing, you might set your Realtime Database rules to allow read/write access:
    ```json
    {
      "rules": {
        ".read": "true",
        ".write": "true"
      }
    }
    ```
    **WARNING:** For production, secure your database rules!

### Configuration

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/abz-mhd/lab-safety-alarm.git
    cd lab-safety-alarm
    ```

2.  **Open `sketch_dec14a.ino`** in the Arduino IDE.

3.  **Update Configuration Variables:** Modify the `#define` and constant values at the beginning of the `sketch_dec14a.ino` file with your specific network credentials, Firebase details, and hardware pin assignments:

    ```cpp
    // Wi-Fi Configuration
    #define SSID "YOUR_WIFI_SSID" // Your Wi-Fi network SSID
    #define PASSWORD "YOUR_WIFI_PASSWORD" // Your Wi-Fi network password

    // Firebase Configuration (from your Firebase project)
    #define FIREBASE_HOST "YOUR_FIREBASE_PROJECT_ID.firebaseio.com" // e.g., "my-project-12345.firebaseio.com"
    #define FIREBASE_AUTH "YOUR_FIREBASE_WEB_API_KEY" // From Project settings -> Web API Key

    // Sensor & Actuator Pin Definitions (Adjust based on your wiring)
    #define DHTPIN 13          // DHT11/22 sensor data pin
    #define GAS_PIN 34         // Analog pin for MQ series gas sensor
    #define FLAME_PIN 35       // Analog pin for Flame sensor
    #define BUZZER_PIN 27      // Pin for buzzer
    #define FAN_PIN 26         // Pin for DC fan control
    #define SERVO_PIN 14       // Pin for servo motor
    #define RED_LED 25         // Pin for Red LED (Danger)
    #define YELLOW_LED 33      // Pin for Yellow LED (Warning)
    #define GREEN_LED 32       // Pin for Green LED (Safe)
    #define BUTTON_PIN 5       // Pin for manual alarm button

    // LCD Configuration
    #define LCD_COLS 16        // Number of columns on your LCD (e.g., 16 or 20)
    #define LCD_ROWS 2         // Number of rows on your LCD (e.g., 2 or 4)
    #define LCD_ADDR 0x27      // I2C address of your LCD (Commonly 0x27 or 0x3F)

    // Safety Thresholds (Adjust as per lab requirements)
    #define TEMP_THRESHOLD_HIGH 30.0   // Celsius
    #define TEMP_THRESHOLD_LOW 18.0    // Celsius
    #define HUMIDITY_THRESHOLD_HIGH 70.0 // Percentage
    #define HUMIDITY_THRESHOLD_LOW 30.0  // Percentage
    #define GAS_THRESHOLD 1500         // Analog reading (higher value means higher concentration)
    #define FLAME_THRESHOLD 1000       // Analog reading (lower value means closer flame)
    ```

### Wiring

Connect your hardware components to the ESP32 board according to the pin definitions configured above. Ensure proper power supply and pull-up/down resistors where necessary for sensors.

### Uploading the Sketch

1.  Connect your ESP32 board to your computer via a USB cable.
2.  In the Arduino IDE, select the correct COM Port for your ESP32 from `Tools > Port`.
3.  Click the "Upload" button (right arrow icon) in the Arduino IDE to compile and upload the `sketch_dec14a.ino` code to your ESP32.
4.  Open the Serial Monitor (`Tools > Serial Monitor`) to view debug messages and ensure Wi-Fi connection and Firebase communication are successful.

## 📁 Project Structure

```
lab-safety-alarm/
├── sketch_dec14a.ino   # Main Arduino sketch containing all logic and configurations
└── README.md           # Project documentation
```

## ⚙️ How It Works

The system operates in a continuous loop:

1.  **Sensor Reading:** The ESP32 reads data from the DHT11/22 (temperature & humidity), MQ-series gas sensor (analog value for gas concentration), and flame sensor (analog value for flame proximity).
2.  **Hazard Assessment:** It compares the current sensor readings against predefined safety thresholds.
3.  **Automated Response:**
    *   If any threshold is exceeded (e.g., high gas, flame detected, extreme temperature/humidity), the `alarmActive` flag is set.
    *   Based on `alarmActive`, `manualAlarmActive`, and specific hazard conditions:
        *   The buzzer is activated/deactivated.
        *   The Red, Yellow, or Green LEDs illuminate to indicate the system's status.
        *   The DC fan is turned on if temperature or gas levels are high.
        *   The servo motor rotates to an 'open' or 'close' position, simulating window control.
4.  **Local Display:** The I2C LCD continuously updates to show the latest sensor values, the current time (synchronized via NTP), and the overall alarm status.
5.  **Remote Monitoring:** Periodically, the system pushes all sensor data and alarm states to the Firebase Realtime Database, allowing users to monitor the lab conditions remotely via any internet-connected device.
6.  **Manual Control:** A push button provides an immediate way for users to manually toggle the alarm state, overriding automated responses if needed.

## 🤝 Contributing

We welcome contributions to enhance the Lab Safety Alarm system! If you have suggestions for improvements, new features, or bug fixes, please follow these steps:

1.  Fork the repository.
2.  Create a new branch for your feature (`git checkout -b feature/AmazingFeature`).
3.  Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4.  Push to the branch (`git push origin feature/AmazingFeature`).
5.  Open a Pull Request.

Please ensure your code adheres to good practices and is well-commented, especially within the Arduino sketch.

## 📄 License

This project is licensed under the [MIT License](LICENSE) - see the LICENSE file for details. <!-- TODO: Add a LICENSE file if it doesn't exist -->

## 🙏 Acknowledgments

-   **Espressif Systems:** For the powerful ESP8266 microcontroller.
-   **Arduino Community:** For the IDE, documentation, and a vast ecosystem of libraries.
-   **Adafruit:** For their excellent DHT sensor library.
-   **Frank de Brabander:** For the LiquidCrystal_I2C library.
-   **mobizt:** For the Firebase ESP8266 Client library.
-   **Kevin Harrington:** For the ESP8266Servo library.
-   **Fabrice Weinberg:** For the NTPClient library.

## 📞 Support & Contact

-   🐛 Issues: [GitHub Issues](https://github.com/abz-mhd/lab-safety-alarm/issues)

---

<div align="center">

**⭐ Star this repo if you find it helpful!**

Made with ❤️ by [abz-mhd](https://github.com/abz-mhd)

</div>
