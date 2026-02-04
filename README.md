# 🌾 Smart Farming Assistant  
### An IoT & Cloud-Based Intelligent Agriculture Solution

---

## 📌 Overview
**Smart Farming Assistant** is an IoT-based automation and monitoring system built to tackle real agricultural challenges such as over/under irrigation, high manual monitoring effort, and crop damage due to animals or intruders.  
It uses **ESP32**, multiple environmental sensors, and **Blynk IoT Cloud** to deliver real-time insights, intelligent irrigation, and security alerts through a mobile app.

---

## 🎯 Problem Statement
Farmers often face:
- Water wastage due to over-irrigation
- Crop stress due to under-irrigation
- High labor and travel costs for monitoring
- Crop damage from animals/intruders
- Lack of real-time, remote visibility

---

## ✅ Objectives
- Real-time monitoring of soil and environment
- Crop-specific, night-only automated irrigation
- Reduced water usage and manual labor
- Reliable intrusion detection with minimal false alarms
- Cloud-based control, status, and notifications
- Scalable architecture for future enhancements

---

## 🛠️ Hardware Components
### Controller
- **ESP32** – Sensor acquisition, logic, and cloud communication

### Sensors
- **Soil Moisture Sensor (4-pin)** – Analog soil moisture
- **DHT11** – Temperature & humidity
- **BH1750 (I²C)** – Light intensity (lux) for day/night detection
- **PIR Motion Sensor** – Motion detection
- **Sound Sensor (AO + DO)** – Sound event detection (used with PIR)

### Actuators
- **DC Water Pump**
- **L298N Motor Driver** – Safe motor control with external power
- **Buzzer** – Audible alert / scarecrow mechanism

### Power
- External battery + buck converter
- Separate motor and ESP32 power paths
- Common ground for stability

---

## 💻 Software & Cloud
- **Arduino IDE**
- **Embedded C / Arduino C++**
- **Blynk IoT Cloud**
  - Mobile dashboard
  - Manual controls
  - Live status LEDs
  - Push notifications via Events

---

## ⚙️ System Architecture



---

## 🚰 Irrigation Logic
The pump turns **ON only when all conditions are met**:
- Motor Enable = ON (from app)
- Soil moisture < crop-specific ideal value
- Light intensity < 10 lux (**Night**)
- Time-limited run (10 minutes)

**Benefits:** reduced evaporation, water efficiency, crop-aware irrigation.

---

## 🚨 Security Logic
- **Sensor fusion:** PIR + Sound
- Buzzer activates only when **motion AND sound** are detected
- Minimizes false alarms (wind, random noise)

---

## 📱 Mobile App (Blynk IoT)
- Live data: soil moisture, temperature, humidity, light
- Crop selection (menu)
- Ideal crop parameters display
- Manual controls: motor & buzzer
- Status LEDs: day/night, motor, buzzer
- Push notifications:
  - Intrusion detected
  - Motor turned ON

---

## 🌾 Supported Crops & Ideal Values

| Crop | Soil % | Temp (°C) | Humidity % |
|---|---:|---:|---:|
| Paddy | 70 | 30 | 80 |
| Wheat | 55 | 25 | 60 |
| Maize | 60 | 28 | 65 |
| Sugarcane | 75 | 32 | 75 |
| Cotton | 50 | 30 | 55 |
| Potato | 65 | 20 | 70 |
| Tomato | 60 | 26 | 65 |
| Onion | 55 | 22 | 60 |
| Banana | 80 | 30 | 85 |
| Pulses | 50 | 27 | 55 |
| Vegetables | 60 | 25 | 65 |
| Tea | 70 | 22 | 80 |

---

## 🔔 Notifications (Blynk Events)
Implemented using **Blynk IoT Events** with anti-spam logic:
- `pir_alert` – Motion detected
- `sound_alert` – Sound detected
- `motor_on` – Irrigation started

---

## ⚠️ Challenges & Solutions

| Challenge | Solution |
|---|---|
ESP32 crashes on motor start | External regulated power + noise suppression |
False PIR triggers | Pull-down resistor + `INPUT_PULLDOWN` |
Sound false alarms | AO + DO validation |
ADC/I²C noise | Filtering & safe reads |
Over-irrigation | Crop thresholds + time limit |

---

