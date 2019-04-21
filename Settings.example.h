//Hostname of ESP8266
#define WIFI_HOSTNAME "C02Logger"

//Wifi SSID to connect to
#define WIFI_SSID "<wifi name>"

//Passowrd for WIFI
#define WIFI_PASSWORD "<wifi password>"

//set the mqqt host name or ip address to your mqqt host. Leave empty to disable mqtt.
#define MQTT_HOST_NAME  "<mqtt host IP>"

//mqtt port for the above host
#define MQTT_PORT       1883

//if authentication is enabled for mqtt, set the username below. Leave empty to disable authentication
#define MQTT_USER_NAME  "<mqtt username>"

//password for above user
#define MQTT_PASSWORD   "<mqtt password>"

//mqtt topic for posting info
#define MQTT_TOPIC "co2meter"

//update interval for fast changing values in milliseconds for mqtt (10 sec)
#define MQTT_UPDATE_INTERVAL  10000

//update interval for CO2
#define SENSOR_MEASUREMENT_FREQUENCY 30000

//disable screen
#define USE_SCREEN true

//show Wifi and mqtt status on screen
#define SHOW_CONNECTION_STATUS true

//uses for debugging, serial print info
#define DEBUGE_MODE true