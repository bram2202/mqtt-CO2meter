// MQTT - Co2 meter + LCD 
//
// TODO
// - WIFI (X)
// - OTA  (X)
// - LCD  ( )
// - MQTT (X)
// - CO2  ( )


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include "ESP8266mDNS.h"
#include "Settings.h"
#include <ArduinoOTA.h>
#include "MQTTPublisher.h"

// Vars
uint32_t lastSend = 0;

MQTTPublisher mqqtPublisher(DEBUGE_MODE);
WiFiUDP ntpUDP;

void setup() {

  if(DEBUGE_MODE)
    Serial.begin(115200);

  Serial.println("Booting");

  // Setup Wifi
  WiFi.mode(WIFI_STA);
  WiFi.hostname(WIFI_HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start OTA
  ArduinoOTA.setHostname("CO2Logger");
  ArduinoOTA.onStart([]() {
    Serial.println("Start Ota");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd Ota");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  // Start processes
  mqqtPublisher.start();
}

void loop() {  
  ArduinoOTA.handle();
  yield();
  mqqtPublisher.handle();
  yield();
}