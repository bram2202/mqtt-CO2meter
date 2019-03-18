#pragma once
#include <Arduino.h>

extern int lastPPM;
extern uint32_t lastUpdate;
extern bool hasMQTT;
extern bool hasWIFI;

class OledScreen
{
  private:
    bool debugMode;

  public:
    OledScreen(bool inDebugMode = false);
    void start();
    void handle();
};