#include "MQTTPublisher.h"
#include "Settings.h"

WiFiClient espClient;
PubSubClient client(espClient);

uint32_t lastUpdateMqtt;

MQTTPublisher::MQTTPublisher(bool inDebugMode)
{
  randomSeed(micros());
  debugMode = inDebugMode;
}

MQTTPublisher::~MQTTPublisher()
{
  client.publish("CO2Meter", "offline");
  client.disconnect();
}


bool MQTTPublisher::reconnect()
{
  lastConnectionAttempt = millis();
  
  if (debugMode)
  {
    Serial.print("MQTT) Attempt connection to server: ");
    Serial.print(MQTT_HOST_NAME);
  }

  // Create a random client ID
  String clientId = "CO2Meter-";
  clientId += String(random(0xffff), HEX);

  // Attempt to connect
  bool clientConnected;
  if (String(MQTT_USER_NAME).length())
  {
    Serial.println("MQTT) Connecting with credientials");
    clientConnected = client.connect(clientId.c_str(), MQTT_USER_NAME, MQTT_PASSWORD);
  }
  else
  {
    Serial.println("MQTT) Connecting without credentials");
    clientConnected = client.connect(clientId.c_str());
  }

  if (clientConnected)
  {
    if (debugMode) {
      Serial.println("MQTT) connected");
    }

    hasMQTT = true;

    // Once connected, publish an announcement...
    client.publish("CO2Meter", "online");

    return true;
  } else {

    if (debugMode)
    {
      Serial.print("MQTT)  failed, rc=");
      Serial.print(client.state());
    }

  }

  return false;
}


void MQTTPublisher::start()
{
  if (String(MQTT_HOST_NAME).length() == 0 || MQTT_PORT == 0)
  {
    Serial.println("MQTT) disabled. No hostname or port set.");
    return; //not configured
  }

  if (debugMode){
    Serial.println("MQTT) enabled. Connecting.");
  }

  client.setServer(MQTT_HOST_NAME, MQTT_PORT);
  reconnect();
  isStarted = true;
}

void MQTTPublisher::stop()
{
  isStarted = false;
}

void MQTTPublisher::handle()
{
  if (!isStarted)
    return;

  if (!client.connected() && millis() - lastConnectionAttempt > RECONNECT_TIMEOUT) {
    hasMQTT = false;
    if (!reconnect()) return;
  }

  //got a valid mqtt connection. Loop through the inverts and send out the data if needed
  client.loop();

  bool send = millis() - lastSentUpdate > MQTT_UPDATE_INTERVAL;
  bool sendOk = true; //if a mqtt message fails, wait for retransmit at a later time
  if (hasWIFI &&  send)
  {
    
    auto mqttTopic = MQTT_TOPIC;
    if (send)
    {      
      uint32_t currentTime = millis();
      if (currentTime - lastUpdateMqtt > SEND_FREQUENCY ) {
        
        if (debugMode){
          Serial.println("MQTT) SEND");
        }

        // Check if last send value differs from new value
        if( lastPPM == sendPPM){
          return;
        }

        lastUpdateMqtt = currentTime;
        // SEND MQTT
        publishOnMQTT(mqttTopic, "/eco2", String(lastPPM));

      }

    }
    
    client.loop();

  }

  if (send)
    lastSentUpdate = millis();
}

bool MQTTPublisher::publishOnMQTT(String prepend, String topic, String value)
{
  auto retVal =  client.publish((prepend.c_str() + topic).c_str(), value.c_str());
  yield();
  return retVal;
}
