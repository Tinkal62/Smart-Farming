#define BLYNK_TEMPLATE_ID "TMPL3hsNjxfCU"
#define BLYNK_TEMPLATE_NAME "Smart Farming"
#define BLYNK_AUTH_TOKEN "WS75-JOFFdlwMnFrLLCptBsuBCS1h1op"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

/* ================= WIFI ================= */
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Galaxy M02s2607";
char pass[] = "g0123456";

/* ================= PINS ================= */
#define DHTPIN 4
#define DHTTYPE DHT11

#define SOIL_AO    34
#define SOUND_DO   26
#define SOUND_AO   35
#define PIR_PIN    14
#define BUZZER_PIN 25

#define MOTOR_IN1 18
#define MOTOR_IN2 19
#define MOTOR_ENA 23

/* ================= CONSTANTS ================= */
#define SOUND_ANALOG_THRESHOLD 400
#define NIGHT_LUX_THRESHOLD 10
#define IRRIGATION_DURATION 600000UL

/* ================= OBJECTS ================= */
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;
BlynkTimer timer;

/* ================= STATES ================= */
bool motorEnable  = false;
bool buzzerEnable = false;
bool motorRunning = false;
bool buzzerRunning = false;

unsigned long motorStartTime = 0;

/* ================= CROP DATA ================= */
int cropID = 0;

int idealSoil[12] = {70,55,60,75,50,65,60,55,80,50,60,70};
int idealTemp[12] = {30,25,28,32,30,20,26,22,30,27,25,22};
int idealHum [12] = {80,60,65,75,55,70,65,60,85,55,65,80};

/* ================= BLYNK INPUT ================= */
BLYNK_WRITE(V9)  { motorEnable  = param.asInt(); }
BLYNK_WRITE(V10) { buzzerEnable = param.asInt(); }
BLYNK_WRITE(V11) { cropID       = param.asInt(); }

/* =================================================
   MAIN FUNCTION
   ================================================= */
void readSensors() {

  /* ---------- DHT ---------- */
  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)) return;

  /* ---------- LIGHT ---------- */
  float lux = lightMeter.readLightLevel();
  if (lux < 0) lux = 0;
  bool isNight = (lux < NIGHT_LUX_THRESHOLD);

  /* ---------- SOIL ---------- */
  int soilRaw = analogRead(SOIL_AO);
  soilRaw = constrain(soilRaw, 0, 4095);
  int soilPct = map(soilRaw, 4095, 1500, 0, 100);

  /* ---------- SOUND + PIR ---------- */
  int soundAO = analogRead(SOUND_AO);
  int soundDO = digitalRead(SOUND_DO);
  int pir     = digitalRead(PIR_PIN);

  bool validSound = (soundDO == HIGH && soundAO > SOUND_ANALOG_THRESHOLD);
  bool intrusion  = validSound && pir;

  /* ---------- SEND LIVE SENSOR DATA ---------- */
  Blynk.virtualWrite(V1, soilPct);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);
  Blynk.virtualWrite(V4, lux);
  Blynk.virtualWrite(V5, validSound ? 255 : 0);
  Blynk.virtualWrite(V6, pir ? 255 : 0);
  Blynk.virtualWrite(V18, isNight ? 0 : 255);   // 🌙 Day/Night LED

  /* ---------- SEND IDEAL CROP VALUES ---------- */
  Blynk.virtualWrite(V13, idealSoil[cropID]);
  Blynk.virtualWrite(V14, idealTemp[cropID]);
  Blynk.virtualWrite(V15, idealHum[cropID]);

  /* ---------- MOTOR LOGIC ---------- */
  bool soilDry = (soilPct < idealSoil[cropID]);
  bool shouldMotorRun = motorEnable && isNight && soilDry;

  if (shouldMotorRun && !motorRunning) {
    motorRunning = true;
    motorStartTime = millis();
  }

  if (!shouldMotorRun) motorRunning = false;

  if (motorRunning && millis() - motorStartTime >= IRRIGATION_DURATION)
    motorRunning = false;

  digitalWrite(MOTOR_IN1, motorRunning);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_ENA, motorRunning);

  Blynk.virtualWrite(V16, motorRunning ? 255 : 0);

  /* ---------- BUZZER ---------- */
  buzzerRunning = buzzerEnable && intrusion;
  digitalWrite(BUZZER_PIN, buzzerRunning);
  Blynk.virtualWrite(V17, buzzerRunning ? 255 : 0);

  /* ---------- SERIAL MONITOR ---------- */
  Serial.println("========== SYSTEM STATUS ==========");
  Serial.print("Crop ID: "); Serial.println(cropID);
  Serial.print("Ideal Soil (%): "); Serial.println(idealSoil[cropID]);
  Serial.print("Ideal Temp (C): "); Serial.println(idealTemp[cropID]);
  Serial.print("Ideal Hum (%): "); Serial.println(idealHum[cropID]);
  Serial.print("Soil (%): "); Serial.println(soilPct);
  Serial.print("Temp (C): "); Serial.println(temperature);
  Serial.print("Humidity (%): "); Serial.println(humidity);
  Serial.print("Lux: "); Serial.println(lux);
  Serial.print("Night: "); Serial.println(isNight);
  Serial.print("PIR: "); Serial.println(pir);
  Serial.print("Sound Valid: "); Serial.println(validSound);
  Serial.print("Soil Raw: "); Serial.println(soilRaw);
  Serial.println("=================================\n");
}

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT_PULLDOWN);
  pinMode(SOUND_DO, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_ENA, OUTPUT);

  dht.begin();
  Wire.begin(21, 22);
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, readSensors);
}

/* ================= LOOP ================= */
void loop() {
  Blynk.run();
  timer.run();
}
