#include "Co2Sensor.h"
#include "Settings.h"
#include <Wire.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;
uint32_t lastUpdateCo2;

Co2Sensor::Co2Sensor(bool inDebugMode)
{
  debugMode = inDebugMode;
}

void Co2Sensor::start()
{
  if (debugMode){ 
    Serial.println("CO2) Start ");
  }

  // Start Sensor
  if (! sgp.begin()){
    if (debugMode){ 
      Serial.println("CO2) Sensor not found");
    }    
  }
}

void Co2Sensor::handle()
{

  uint32_t currentTime = millis();
  if (currentTime - lastUpdateCo2 > SEND_FREQUENCY ) {
    
    if (! sgp.IAQmeasure()) {
      if (debugMode){
        Serial.println("CO2)Measurement failed");
      }
      return;
    }

    lastPPM = sgp.eCO2;  
    lastUpdateCo2 = millis();    
   
    if (debugMode){
      Serial.println("CO2) updated");
    }
  }
}