#include "MQTT.h"

WiFiClient espClient;
PubSubClient pubSubClient(espClient);
WeatherObject weatherObject;

void setupMQTT(){
  pubSubClient.setServer(MQTT_SERVER, 1883);
  #if MODE==1
  pubSubClient.setCallback(callback);
  #endif
  if (!pubSubClient.connected()) {
      reconnect();
    }
  weatherObject.windspeed = 0;
  weatherObject.temperature = 0;
  weatherObject.humidity = 0;
}

void MQTTLoop()
{
  pubSubClient.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg;
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg += (char)payload[i];
  }
  Serial.println();
  if(!strcmp(topic,"room/ledstrip/status"))
  {
    Serial.println("ledstrip " + msg);
  }
  if(!strcmp(topic,"room/ledstrip/color"))
  {
    Serial.println("ledstrip " + msg);
  }
  Serial.println(msg.toInt());
  if(!strcmp(topic,"outside/Windspeed"))
  {
    weatherObject.windspeed = msg.toInt();
  }
  if(!strcmp(topic,"outside/Temperature"))
  {
    weatherObject.temperature = msg.toInt();
  }
  if(!strcmp(topic,"outside/Humidity"))
  {
    weatherObject.humidity = msg.toInt();
  }

  if(weatherObject.temperature != 0 && weatherObject.humidity != 0)
  {
    displayOnScreen(weatherObject);
    sendPackage(weatherObject);
  }
}

void reconnect() {
  // Loop until we're reconnected
  #if MODE==1
  while (!pubSubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    Serial.println("SERVER");
    if (pubSubClient.connect("server",USERNAME,PASSWORD)) {
      Serial.println("Connected");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(pubSubClient.state());
      if (millis() >= 10000)
      {
        ESP.deepSleep(20e6);
      }
    }
  }
  #endif

  #if MODE==0
  while (!pubSubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    Serial.println("CLIENT");
    if (pubSubClient.connect("client",USERNAME,PASSWORD)) {
      Serial.println("Connected");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(pubSubClient.state());
      if (millis() >= 10000)
      {
        ESP.deepSleep(20e6);
      }
    }
  }
  #endif
}

void publishMessage(String topic, int x)
{
  char buf[5];
  Serial.println(topic + ":" + itoa(x,buf,10));
  pubSubClient.publish(topic.c_str(), itoa(x,buf,10));
}

void subscribeToTopic(String topic)
{
  pubSubClient.subscribe(topic.c_str());
}
