#ifndef MQTT_H
#define MQTT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "WeatherObject.h"
#include "Display.h"
#include "Json.h"

#define MQTT_SERVER "m23.cloudmqtt.com"
#define USERNAME "wqqelofh"
#define PASSWORD "auJy6Ux2Q_gF"

void setupMQTT();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void MQTTLoop();
void publishMessage(String topic, int x);
void subscribeToTopic(String topic);

#endif
