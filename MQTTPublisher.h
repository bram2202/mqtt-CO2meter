#define MQTT_SOCKET_TIMEOUT 5
#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <vector>
#include "PubSubClient.h"
#include "WiFiClient.h"

#define RECONNECT_TIMEOUT 15000

extern uint32_t lastUpdate;
extern bool hasMQTT;
extern bool hasWIFI;

class MQTTPublisher
{
  private:
    bool debugMode;
    bool isStarted;

    unsigned long lastConnectionAttempt = 0; // last reconnect
    unsigned long lastSentUpdate = 0;	// last update 

    bool publishOnMQTT(String prepend, String topic, String value);
    bool reconnect();
  public:
    MQTTPublisher(bool inDebugMode = false);
    ~MQTTPublisher();

    void start();
    void stop();

    void handle();
};
