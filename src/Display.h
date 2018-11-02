#ifndef Display_H
#define Display_H

#include "Nextion.h"
#include <String.h>
#include "WeatherObject.h"
#include <ESP8266WiFi.h>
#include "Light.h"
#include "NTPTime.h"

void setupDisplay();
void b0PopCallback(void *ptr);
void b1PopCallback(void *ptr);
void redSliderPopCallback(void *ptr);
void greenSliderPopCallback(void *ptr);
void blueSliderPopCallback(void *ptr);
void displayLoop();
void displayOnScreen(WeatherObject x);
void displayOnScreen(IPAddress x);
void displayOnScreen(String x, String y);

#endif
