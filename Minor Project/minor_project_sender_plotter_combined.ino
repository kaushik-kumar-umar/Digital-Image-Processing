#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu(Wire);

// ---------------- WIFI ----------------
const char* ssid = "abc";
const char* password = "12345678";

String scriptURL = "https://script.google.com/macros/s/AKfycbwPX1yzdpe14nah6DeThcLPICALzzylfZpI0991R8ikvLxv2rj3wGrnAW1IV_5-H_X_Kw/exec";

// -------- Kalman parameters ----------
float Q1 = 1;
float R1 = 10;

float Q2 = 1;
float R2 = 100;

// -------- Accelerometer filters -------
float P_ax1 = 1;
float X_ax1 = 0;

float P_ax2 = 1;
float X_ax2 = 0;

// -------- Gyroscope filters ----------
float P_gx1 = 1;
float X_gx1 = 0;

float P_gx2 = 1;
float X_gx2 = 0;

unsigned long lastSend = 0;

void setup() {

  Serial.begin(115200);
  Wire.begin();

  mpu.begin();
  mpu.calcGyroOffsets(true);

  Serial.println("RawAcc,KalAcc1,KalAcc2,RawGyro,KalGyro1,KalGyro2");

  // -------- WIFI ----------
  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" Connected!");
}

void loop() {

  mpu.update();

  float ax = mpu.getAccX();
  float gx = mpu.getGyroX();

  // -------- ACCEL FILTER 1 ----------
  P_ax1 = P_ax1 + Q1;
  float K_ax1 = P_ax1 / (P_ax1 + R1);
  X_ax1 = X_ax1 + K_ax1 * (ax - X_ax1);
  P_ax1 = (1 - K_ax1) * P_ax1;

  // -------- ACCEL FILTER 2 ----------
  P_ax2 = P_ax2 + Q2;
  float K_ax2 = P_ax2 / (P_ax2 + R2);
  X_ax2 = X_ax2 + K_ax2 * (ax - X_ax2);
  P_ax2 = (1 - K_ax2) * P_ax2;

  // -------- GYRO FILTER 1 ----------
  P_gx1 = P_gx1 + Q1;
  float K_gx1 = P_gx1 / (P_gx1 + R1);
  X_gx1 = X_gx1 + K_gx1 * (gx - X_gx1);
  P_gx1 = (1 - K_gx1) * P_gx1;

  // -------- GYRO FILTER 2 ----------
  P_gx2 = P_gx2 + Q2;
  float K_gx2 = P_gx2 / (P_gx2 + R2);
  X_gx2 = X_gx2 + K_gx2 * (gx - X_gx2);
  P_gx2 = (1 - K_gx2) * P_gx2;

  // -------- SERIAL PLOTTER ----------
  Serial.print(ax);
  Serial.print(",");
  Serial.print(X_ax1);
  Serial.print(",");
  Serial.print(X_ax2);
  Serial.print(",");
  Serial.print(gx);
  Serial.print(",");
  Serial.print(X_gx1);
  Serial.print(",");
  Serial.println(X_gx2);

  // -------- SEND TO GOOGLE SHEETS EVERY 3s ----------
  if (millis() - lastSend > 3000) {

    if (WiFi.status() == WL_CONNECTED) {

      HTTPClient http;

      String url = scriptURL +
                   "?ax=" + String(ax) +
                   "&kax1=" + String(X_ax1) +
                   "&kax2=" + String(X_ax2) +
                   "&gx=" + String(gx) +
                   "&kgx1=" + String(X_gx1) +
                   "&kgx2=" + String(X_gx2);

      http.begin(url);
      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.println("Data sent to Google Sheets");
      }

      http.end();
    }

    lastSend = millis();
  }

  delay(50);
}