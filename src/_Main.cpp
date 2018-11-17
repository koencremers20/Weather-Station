#include "Arduino.h"
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SoftwareSerial.h>
#include "Json.h"
#include "Send.h"
#include "DHTSensor.h"
#include "WindForceSensor.h"
#include "OTA.h"
#include "MQTT.h"
#include <PubSubClient.h>
#include "Display.h"
#include "NTPTime.h"

#define SERVER MODE
#define BAUD_RATE 57600
#define DEEPSLEEPTIMER 20e6

int temp = 0;
int hum = 0;
int windforce =  0;

ESP8266WiFiMulti wifiMulti;

PubSubClient _pubSubClient;
// #region CLIENT
#if SERVER==0

WiFiClient client;

void setup(){
  Serial.begin(BAUD_RATE);
  Serial.println("MODE CLIENT");
  setupDHT();
  setupWindForceSensor();
  temp = getTemperature();
  hum = getHumidity();
  windforce = getWindForce();
  // #region WiFi
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("*****", "*****");
  wifiMulti.addAP("*****", "***");
  wifiMulti.addAP("***", "******");
  wifiMulti.addAP("****", "*****");
  Serial.println("Connecting Wifi...");
  int startTime = millis();
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    yield();
    if( millis() - startTime > 10000)
    {
        ESP.deepSleep(DEEPSLEEPTIMER);
    }
  }
  setupMQTT();
  delay(1000);
  publishMessage("outside/Windspeed", windforce);
  delay(1000);
  publishMessage("outside/Temperature", temp);
  delay(1000);
  publishMessage("outside/Humidity", hum);
  delay(1000);
  Serial.println("send mqtt packets");
  //String response = sendToServer(client, server, SERVERPORT, temp, hum, windforce);
  //Serial.println(response);
  // #endregion WiFi
  ESP.deepSleep(DEEPSLEEPTIMER); // 20e6 is 20 microseconds
}

void loop () {/*
  temp = getTemperature();
  hum = getHumidity();
  String test = sendToServer(client, server, temp, hum, windforce);
  Serial.println("from server: " + test);
  client.flush();
  delay(2000);     */             // client will trigger the communication after two seconds
}

#endif
// #endregion

// #region SERVER
#if SERVER==1
//WiFiServer WiFiServer(SERVERPORT);

//IPAddress gateway(IP1, IP2, IP3, 1);           // gateway of your network
//IPAddress subnet(255, 255, 255, 0);          // subnet mask of your network

int lastHum = 0;
int lastTemp = 0;

void setup() {
  setupDisplay();
//  mySerial.begin(9600);
  Serial.println("MODE SERVER");
  // #region WiFi
  WiFi.hostname("SERVER");                  // only for debug
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("*****", "*****");
  wifiMulti.addAP("*****", "***");
  wifiMulti.addAP("***", "******");
  wifiMulti.addAP("****", "*****");
  Serial.println("Connecting Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    yield();
    if(millis() > 10000)
    {
        ESP.deepSleep(DEEPSLEEPTIMER);
    }
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //WiFiServer.begin();                         // starts the server
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());  // some parameters from the network
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  // #endregion WiFi
  setupOTA();
  setupMQTT();
  setupTime();

  delay(1000);
  subscribeToTopic("room/ledstrip/status");
  subscribeToTopic("room/ledstrip/color");
  subscribeToTopic("outside/Windspeed");
  subscribeToTopic("outside/Temperature");
  subscribeToTopic("outside/Humidity");

}

void loop () {
  handleOTA();
  MQTTLoop();
  displayLoop();
}

#endif
// #endregion
