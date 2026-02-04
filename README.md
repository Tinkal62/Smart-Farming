🌾 Smart Farming Assistant
An IoT & Cloud-Based Intelligent Agriculture Solution
📌 Project Overview

Smart Farming Assistant is an IoT-based agricultural automation and monitoring system designed to solve real-world farming problems such as over/under irrigation, high manual monitoring cost, and crop damage due to animals or intruders.

The system uses ESP32, multiple environmental sensors, and Blynk IoT Cloud to provide real-time monitoring, intelligent irrigation control, and security alerts, all accessible through a mobile application.

This project focuses on practical deployment challenges like power stability, sensor noise, false alerts, and scalability—bridging the gap between textbook IoT projects and real agricultural use cases.

🎯 Problem Statement

Farmers commonly face:

Over-irrigation and water wastage

Under-irrigation affecting crop yield

Manual monitoring of soil and environment

Crop damage caused by animals and intruders

Lack of real-time remote monitoring

✅ Objectives

Monitor soil and environmental conditions in real time

Automate irrigation based on crop type, soil condition, and time (night-only)

Reduce water wastage and manual labor

Detect intrusions using reliable sensor fusion

Enable remote monitoring and control via cloud

Build a scalable base for future smart agriculture solutions

🛠️ Hardware Components Used
Main Controller

ESP32

Handles sensor readings, decision logic, and cloud communication

Sensors

Soil Moisture Sensor (4-pin)

Measures soil water content (analog output used)

DHT11

Measures temperature and humidity

BH1750 Light Sensor (I²C)

Measures light intensity (lux) for day/night detection

PIR Motion Sensor

Detects movement of humans/animals

Sound Sensor (AO + DO)

Detects sound events (used with PIR to avoid false alerts)

Actuators

Water Pump (DC Motor)

L298N Motor Driver

Safely drives the motor using external power

Buzzer

Audible alert / scarecrow mechanism

Power

External battery + buck converter

Separate power paths for ESP32 and motor

Common ground for stability

💻 Software & Cloud Technologies

Arduino IDE – ESP32 programming

Embedded C / Arduino C++

Blynk IoT Cloud

Real-time dashboard

Mobile app control

Cloud notifications (Events)

🔗 System Architecture (High Level)
Sensors → ESP32 → Decision Logic → Actuators
              ↘
               Blynk IoT Cloud → Mobile App

⚙️ Working Principle
🌱 Sensor Monitoring

Soil moisture, temperature, humidity, and light are read periodically

Values are sent to the Blynk mobile app in real time

🚰 Irrigation Logic

The motor turns ON only when all conditions are satisfied:

Motor Enable = ON (from app)

Soil moisture < crop-specific ideal value

Light intensity < 10 lux (Night condition)

Irrigation duration limited to 10 minutes

This ensures:

Reduced evaporation loss

Water efficiency

Crop-specific irrigation

🚨 Security & Intrusion Detection

PIR + Sound sensor fusion is used

Buzzer activates only when:

Motion is detected AND

Sound crosses threshold

Prevents false alarms caused by wind or noise

📱 Mobile App Features (Blynk IoT)

Live display of:

Soil moisture

Temperature

Humidity

Light intensity

Crop selection (Menu widget)

Display of ideal crop parameters

Manual enable/disable:

Motor

Buzzer

Live status indicators:

Day/Night

Motor ON/OFF

Buzzer ON/OFF

Push notifications for:

Intrusion detection

Motor ON event

🌾 Crops Supported
Crop	Soil %	Temp °C	Humidity %
Paddy	70	30	80
Wheat	55	25	60
Maize	60	28	65
Sugarcane	75	32	75
Cotton	50	30	55
Potato	65	20	70
Tomato	60	26	65
Onion	55	22	60
Banana	80	30	85
Pulses	50	27	55
Vegetables	60	25	65
Tea	70	22	80
🔔 Notifications (Blynk Events)

Implemented using Blynk IoT Events:

pir_alert → Motion detected

sound_alert → Sound detected

motor_on → Irrigation started

Anti-spam logic ensures notifications are sent only once per event.

⚠️ Challenges Faced & Solutions
Challenge	Solution
ESP32 crash when motor turns ON	External regulated power + noise suppression
False PIR detection	Pull-down resistor + INPUT_PULLDOWN
Sound false triggers	Analog + digital validation
ADC & I²C noise	Sensor read filtering
Over-irrigation	Crop-based thresholds + time limit
🔮 Future Scope

ML-based irrigation prediction

Weather API integration

Fertilizer automation

GSM / LoRa support for no-WiFi areas

Solar-powered deployment

Multi-farm cloud dashboard

🚀 How to Run the Project

Clone the repository

git clone https://github.com/your-username/smart-farming-assistant.git


Open the code in Arduino IDE

Install required libraries:

Blynk

DHT sensor library

BH1750 library

Configure:

WiFi credentials

Blynk Template ID & Auth Token

Upload to ESP32

Power ESP32 using external regulated supply

Open Blynk app and monitor live data

📸 Project Status

✔ Hardware prototype completed
✔ Cloud-based mobile app working
✔ Irrigation & intrusion logic implemented
✔ Notifications enabled
🚧 Advanced ML features under development

🤝 Contributors

Tinkal Das

[Teammate Name]

📜 License

This project is open-source and intended for educational and research purposes.

⭐ Acknowledgement

This project helped us understand real-world IoT challenges such as power integrity, sensor noise, and system reliability, moving beyond ideal lab conditions.
