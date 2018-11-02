#ifndef DHTSensor_H
#define DHTSensor_H

#include "DHT.h"

#define DHTPIN D5
#define DHTTYPE DHT11   // DHT  11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

void setupDHT();
int getHumidity();
int getTemperature();

#endif
