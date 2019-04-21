# C02 logger

Using the small LOLIN D1 mini, a Oled shield and a sensor breakout board, its possible to get a sens of C02 in the air.

For example to use with `Hass.io` [[link]](https://www.home-assistant.io/)

The Oled sceen is optinal and can be disabled in the settings.


### end result

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
* todo

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
| SHOW_CONNECTION_STATUS | true | show wifi and MQTT status |
| DEBUGE_MODE | true | debug mode |

## MQTT
Subscribe to `co2meter/<topic>` in your MQTT client. prefix can be changes in the settings.

| Topic | Description| Unit  |
| ------------- |:-------------:| -----:|
| eco2     | eCO2 value | ppm |
