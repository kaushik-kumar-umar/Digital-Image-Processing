#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu(Wire);

// WiFi credentials
const char* ssid = "abc";
const char* password = "12345678";

// Google script URL
String scriptURL = "https://script.google.com/macros/s/AKfycbxhBd63EYRvrNJpTQoBlh-4KSSKuUYhVoab54wWUfootobkWpG-n5CSMwoeCAFOleSpNg/exec";

void setup() {

  Serial.begin(115200);
  Wire.begin();

  mpu.begin();
  mpu.calcGyroOffsets(true);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected");
}

void loop() {

  mpu.update();

  float ax = mpu.getAccX();
  float gx = mpu.getGyroX();

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String url = scriptURL + "?ax=" + String(ax) + "&gx=" + String(gx);

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("Data sent");
    } else {
      Serial.println("Error sending");
    }

    http.end();
  }

  delay(2000);  // send every 2 seconds
}