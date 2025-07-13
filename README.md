## Smart Home System Based on Task Scheduler

A multi-sensor smart environment control system using DHT11, IR, LDR, and Gas sensors. The system automates fans, lights, buzzers, and LEDs based on real-time data using non-blocking scheduled tasks.

---

## 🚀 Features

- 🌡️ Temperature and Humidity monitoring using DHT11
- 🔦 Light detection using LDR
- 🔥 Gas/smoke detection using MQx sensor
- 🕴️ Motion detection using IR sensor
- ⚡ Relays to control fan and light
- 🔔 Buzzer alerts and LEDs for visualization
- ⏱️ TaskScheduler for efficient task management

---

## 🛠️ Hardware Requirements

- NodeMCU / ESP8266 / Arduino Uno
- DHT11 Sensor
- IR Obstacle Sensor
- LDR Module
- MQ-2 or MQ-135 Gas Sensor
- 2-Channel Relay Module
- Buzzer
- LEDs (x4)
- Breadboard and jumper wires

---

## 🧠 How It Works

| Sensor      | Pin     | Purpose                   |
|-------------|---------|---------------------------|
| DHT11       | D7      | Reads temperature/humidity|
| IR Sensor   | A1      | Detects motion            |
| LDR         | D6      | Detects light levels      |
| Gas Sensor  | D2      | Detects smoke/gas         |
| Relay 1     | D4      | Controls FAN              |
| Relay 2     | D5      | Controls Light            |
| Buzzer      | D10     | Alerts on motion          |
| LEDs        | D9–D13  | Visual indicators         |

- Tasks run in parallel using `TaskScheduler`.
- FAN and light are automated based on temperature and LDR data.
- Buzzer and LEDs indicate motion and smoke presence.

---

## 📦 Libraries Used

Install these from Arduino Library Manager:

- `TaskScheduler` by Arkhipenko
- `DHT sensor library` by Adafruit
- `Adafruit Unified Sensor`

---

## 🧪 Usage

1. Clone the repository.
2. Open the `.ino` file in Arduino IDE.
3. Install required libraries.
4. Upload the code.
5. Open Serial Monitor (115200 baud) for live logs.

---

## 👨‍💻 Author

**Rithvidas Rathish**  
Embedded Systems | IoT | Firmware | AIoT  
https://www.linkedin.com/in/rithvidas-rathish-embedded-firmware-developer/
📫 Feel free to connect for collaborations!

---
