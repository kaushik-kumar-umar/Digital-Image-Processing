#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu(Wire);

// -------- Kalman parameters --------
float Q1 = 1;
float R1 = 10;

float Q2 = 1;
float R2 = 100;

// -------- Accelerometer filters --------
float P_ax1 = 1;
float X_ax1 = 0;

float P_ax2 = 1;
float X_ax2 = 0;

// -------- Gyroscope filters --------
float P_gx1 = 1;
float X_gx1 = 0;

float P_gx2 = 1;
float X_gx2 = 0;

void setup() {

  Serial.begin(115200);
  Wire.begin();

  mpu.begin();
  mpu.calcGyroOffsets(true);
}

void loop() {

  mpu.update();

  float ax = mpu.getAccX();
  float gx = mpu.getGyroX();

  // ---------- ACCELEROMETER FILTER 1 ----------
  P_ax1 = P_ax1 + Q1;
  float K_ax1 = P_ax1 / (P_ax1 + R1);
  X_ax1 = X_ax1 + K_ax1 * (ax - X_ax1);
  P_ax1 = (1 - K_ax1) * P_ax1;

  // ---------- ACCELEROMETER FILTER 2 ----------
  P_ax2 = P_ax2 + Q2;
  float K_ax2 = P_ax2 / (P_ax2 + R2);
  X_ax2 = X_ax2 + K_ax2 * (ax - X_ax2);
  P_ax2 = (1 - K_ax2) * P_ax2;

  // ---------- GYRO FILTER 1 ----------
  P_gx1 = P_gx1 + Q1;
  float K_gx1 = P_gx1 / (P_gx1 + R1);
  X_gx1 = X_gx1 + K_gx1 * (gx - X_gx1);
  P_gx1 = (1 - K_gx1) * P_gx1;

  // ---------- GYRO FILTER 2 ----------
  P_gx2 = P_gx2 + Q2;
  float K_gx2 = P_gx2 / (P_gx2 + R2);
  X_gx2 = X_gx2 + K_gx2 * (gx - X_gx2);
  P_gx2 = (1 - K_gx2) * P_gx2;

  // ---------- SERIAL PLOTTER ----------
  Serial.print(ax);      // Raw accel
  Serial.print(",");
  Serial.print(X_ax1);   // Kalman Q1,R1
  Serial.print(",");
  Serial.print(X_ax2);   // Kalman Q2,R2
  Serial.print(",");
  Serial.print(gx);      // Raw gyro
  Serial.print(",");
  Serial.print(X_gx1);   // Kalman Q1,R1
  Serial.print(",");
  Serial.println(X_gx2); // Kalman Q2,R2

  delay(50);
}