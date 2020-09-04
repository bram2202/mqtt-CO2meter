#pragma once
#include <Arduino.h>

extern int lastEco2;
extern int lastTVoc;

class Co2Sensor
{
  private:
    bool debugMode;
    uint32_t lastSensorUpdate;

  public:
    Co2Sensor(bool inDebugMode = false);
    void start();
    void handle();
};
