#include "OledScreen.h"
#include "Settings.h"
#include <Wire.h>
#include <LOLIN_I2C_BUTTON.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

I2C_BUTTON button(DEFAULT_I2C_BUTTON_ADDRESS); //I2C Address 0x31

String keyString[] = {"None", "Press", "Long", "Double", "Hold"};

OledScreen::OledScreen(bool inDebugMode)
{
  debugMode = inDebugMode;
}

// start screen en display text
void OledScreen::start()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 20); // col, row
    display.println("Booting..");
    display.display();
    // sleep
    delay(500);
    handle();
}


void OledScreen::handle()
{
    if (button.get() == 0) // Button press
    {
        if (button.BUTTON_A)
        {
            if (debugMode){
                Serial.println("Button A pressed");
            }
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("A: ");
            display.println(keyString[button.BUTTON_A]);
            display.display();
            delay(2000);
        }

        if (button.BUTTON_B)
        {
            if (debugMode){
                Serial.println("Button B pressed");
            }
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("B: ");
            display.println(keyString[button.BUTTON_B]);
            display.display();

            delay(2000);
        }
           
        display.clearDisplay();

        // if set, WIFI and MQTT status is shows
        if(SHOW_CONNECTION_STATUS)
        {
            if(hasWIFI)
            {
                display.setCursor(0, 0);
                display.println("WIFI: Y");
            }
            else
            {
                display.setCursor(0, 0);
                display.println("WIFI: N");
            }

            if(hasMQTT)
            {
                display.setCursor(0, 10);
                display.println("MQTT: Y");
            }
            else
            {
                display.setCursor(0, 10);
                display.println("MQTT: N");
            }

            if(lastPPM != 0)
            {
                display.setCursor(15, 30);
                display.println(String(lastPPM) + " ppm");
            }
        }
        else
        {
            if(lastPPM != 0)
            {
                display.setCursor(15, 15);
                display.println(String(lastPPM) + " ppm");
            }
        }


        
        display.display();
    }

    
    
}
