#include "OledScreen.h"
#include "Settings.h"
#include <Wire.h>
#include <LOLIN_I2C_BUTTON.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include "ESP8266mDNS.h"

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
    display.setCursor(0, 0); // col, row
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
        // Display IP
        if (button.BUTTON_A)
        {
            if (debugMode)
            {
                Serial.println("Button A pressed");
            }
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("IP: ");
            display.setCursor(0, 10);
            display.println(WiFi.localIP());
            display.display();
            delay(2000);
        }

        display.clearDisplay();

        // if set, WIFI and MQTT status is shows
        if (SHOW_CONNECTION_STATUS)
        {
            if (hasWIFI)
            {
                display.setCursor(0, 0);
                display.println("WIFI: Y");
            }
            else
            {
                display.setCursor(0, 0);
                display.println("WIFI: N");
            }

            if (hasMQTT)
            {
                display.setCursor(0, 10);
                display.println("MQTT: Y");
            }
            else
            {
                display.setCursor(0, 10);
                display.println("MQTT: N");
            }

            if (lastEco2 != 0)
            {
                display.setCursor(0, 30);
                display.println("eCO2: " + String(lastEco2));
            }

            if (lastTVoc != 0)
            {
                display.setCursor(0, 40);
                display.println("TVOC: " + String(lastTVoc));
            }
        }
        else
        {
            if (lastEco2 != 0)
            {
                display.setCursor(0, 15);
                display.println("ECO2: " + String(lastEco2));
            }

            if (lastTVoc != 0)
            {
                display.setCursor(0, 25);
                display.println("TVOC: " + String(lastTVoc));
            }
        }

        display.display();
    }
}
