#ifndef Json_H
#define Json_H

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include "WeatherObject.h"

#define idDevice "faedd122-af82-4ba2-99b3-e7078cc4b5f3"
#define ipClassServer "http://hro-sma.nl/api/weatherupdates/"

int sendPackage(WeatherObject x);

#endif
