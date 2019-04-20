#pragma once
#include <Arduino.h>

extern int lastPPM;

class Co2Sensor
{
  private:
    bool debugMode;

  public:
    Co2Sensor(bool inDebugMode = false);
    void start();
    void handle();
};