// https://lastminuteengineers.com/esp8266-ntp-server-date-time-tutorial/
// https://arduinogetstarted.com/tutorials/arduino-relay

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define WIFI_SSID "ISKONOVAC-7FEF40"
#define WIFI_PASS "AA545B3BFB32"
#define RELAY_PIN D4

const long UTC_OFFSET_S = 3600; // UTC +1 -> 1 * 60 * 60 : 3600
const long DELAY_MS = 60000; // 1000 * 60

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_S);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  Serial.begin(9600);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println();

  timeClient.begin();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    while(WiFi.status() != WL_CONNECTED){
      delay(100);
      Serial.print(".");
    }
    Serial.println();
  }

  timeClient.update();
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());

  if(timeClient.getHours() > 7 && timeClient.getHours() < 21) digitalWrite(RELAY_PIN, HIGH);
  else digitalWrite(RELAY_PIN, LOW);

  delay(DELAY_MS);
}
