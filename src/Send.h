#ifndef Send_H
#define Send_H

#include <ESP8266WiFi.h>

String sendToServer(WiFiClient client, IPAddress server, int serverPort, int temp, int humidity, int windForce);

#endif
