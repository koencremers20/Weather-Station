#ifndef WindForceSensor_H
#define WindForceSensor_H

#include <Arduino.h>

#define WindForcePin A0 

void setupWindForceSensor();
int getWindForce();

#endif
