#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define SSID "รหัสบน"        //ใส่ ชื่อ Wifi
#define PASSWORD "รหัสล่าง"  //ใส่ รหัส Wifi

unsigned long period = 1000;  //ระยะเวลาที่ต้องการรอ
unsigned long last_time = 0;  //ประกาศตัวแปรเป็น global เพื่อเก็บค่าไว้ไม่ให้ reset จากการวนloop
int hourNow, minuteNow, secondNow;
const long offsetTime = 25200;  // หน่วยเป็นวินาที จะได้ 7*60*60 = 25200
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", offsetTime);

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  for (int i = 0; i <= 10; i++) {
    if (WiFi.status() != WL_CONNECTED) {
      delay(1000);
    } else {
      Serial.println("My ip : ");
      Serial.println(WiFi.localIP());
      break;
    }
  }
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  timeClient.begin();  // เริ่มการทำงานของ NTPClient
}

void loop() {
  timeClient.update();
  secondNow = timeClient.getSeconds();
  minuteNow = timeClient.getMinutes();
  hourNow = timeClient.getHours();

  if (millis() - last_time > period) {
    last_time = millis();
    Serial.println(hourNow);
    if (hourNow >= 17 && hourNow < 22)  //5โมง เปิดไฟ 4ทุ่ม ปิดไฟ
    {
      Serial.println("เปิดไฟ");
    } else {
      Serial.println("ปิดไฟ");
    }
  }
}