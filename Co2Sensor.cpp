#include "Co2Sensor.h"
#include "Settings.h"
#include <Wire.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;

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

  if (millis() - lastSensorUpdate > SENSOR_MEASUREMENT_FREQUENCY) {
    
    if (! sgp.IAQmeasure()) {
      if (debugMode){
        Serial.println("CO2) Measurement failed");
      }
      return;
    }
    
    lastEco2 = sgp.eCO2;  
    lastTVoc = sgp.TVOC;
    lastSensorUpdate = millis();    
   
    if (debugMode){
      Serial.println("CO2) updated");
    }
  }
}
