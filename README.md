# C02 logger

Using the small LOLIN D1 mini, a Oled shield and a sensor breakout board, its possible to get a sense of CO2 in the air.<br>
Sends both eCO2 ans TVOC.

For example to use with `Hass.io` [[link]](https://www.home-assistant.io/)

The Oled screen is optional and can be disabled in the settings.


### End result

front:

![front](https://github.com/bram2202/mqtt-C02meter/blob/master/docs/front.png "front")

back:

![back](https://github.com/bram2202/mqtt-C02meter/blob/master/docs/back.png "back")

## Requirements 
* ESP8266 (Wemos/LOLIN D1 mini)
* SGP30 eCO2 sensor
* Basic soldering and wiring skills

### Optional
* OLED Shield (Wemos/LOLIN 64x48 I2C)

## Software requirements 
* Oled library [[link]](https://github.com/mcauser/Adafruit_SSD1306/tree/esp8266-64x48)
* SGP library [[link]](https://github.com/adafruit/Adafruit_SGP30)
* Arduino IDE / VS Code
* (For Wemos d1 mini) CH340G driver [[link]](https://wiki.wemos.cc/downloads)

## Connection scheme
The oled shield fits exactly on the ESP, so no other connections are required.

| ESP8266 | SGP30 |  
| :--------- |:-------| 
| 3.3v | VCC  |
| GND  | GND  |
| D1   | SCL  |
| D2   | SDA  |

## Settings
Copy `Settings.example.h` to `Settings.h` and fill in the correct data.

| Setting | default | Description|  
|:------------- |:----- |:-------------:| 
| WIFI_HOSTNAME | C02Logger | device name on network |
| WIFI_SSID | - | Wifi name to connect to |
| WIFI_PASSWORD | - | Wifi password |
| MQTT_HOST_NAME | - | MQTT broker address |
| MQTT_PORT | 1833 | MQTT broker port |
| MQTT_USER_NAME| - | MQTT user name |
| MQTT_PASS | - | MQTT password |
| MQTT_TOPIC | co2meter | MQTT topic prefix |
| MQTT_UPDATE_INTERVAL | 30000 | Send interval (ms) |
| SENSOR_MEASUREMENT_FREQUENCY | 5000 | Sensor update interval (ms) |
| USE_SCREEN | true | Enable or disable screen |
| SHOW_CONNECTION_STATUS | true | Show wifi and MQTT status |
| DEBUGE_MODE | true | Debug mode |

## MQTT
Subscribe to `co2meter/<topic>` in your MQTT client. prefix can be changes in the settings.

| Topic | Description| Unit  |
| ------------- |:-------------:| -----:|
| eco2  | eCO2 value | ppm |
| tvoc  | TVOC value | PPB |
