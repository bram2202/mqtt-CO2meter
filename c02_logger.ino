// MQTT - Co2 meter + LCD 

#include "Settings.h"
#include <ArduinoOTA.h>
#include "MQTTPublisher.h"
#include "OledScreen.h"
#include "WifiConnector.h"
#include "Co2Sensor.h"

// Vars
int lastPPM = 0;
int sendPPM = 0;
bool hasMQTT = false;
bool hasWIFI = false;

MQTTPublisher mqqtPublisher(DEBUGE_MODE);
OledScreen oledScreen(DEBUGE_MODE);
Co2Sensor co2Sensor(DEBUGE_MODE);
WifiConnector wifiConnector(DEBUGE_MODE);
WiFiUDP ntpUDP;

void setup() {

  if(DEBUGE_MODE)
    Serial.begin(115200);

  Serial.println("Booting");

  // Start Screen
  oledScreen.start();

  // Start Co2 sensor
  co2Sensor.start();

  // Start wifi
  wifiConnector.start();

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

  //ArduinoOTA.handle();
  //yield();

  co2Sensor.handle();
  yield();

  mqqtPublisher.handle();
  yield();

  oledScreen.handle();
  yield();

  wifiConnector.handle();
  yield();
}