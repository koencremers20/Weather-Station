#include "WindForceSensor.h"

#define period 20000           // Measurement period (miliseconds)
int lastSensorValue = 0;
int count = 0;     // B/W counter for sensor

void setupWindForceSensor()
{
  pinMode(WindForcePin, INPUT);
}
int getWindForce()
{
  count = 0;
  Serial.println(": Start measurement...");
  unsigned long startTime = millis();
  while (millis() < startTime + period) {
    int sensorValue = analogRead(A0);
     // print out the value you read:
     //Serial.println(sensorValue);
     if (sensorValue < 500) {
       lastSensorValue = sensorValue;
     }
     //Serial.println(lastSensorValue);
     if (lastSensorValue < 500 && sensorValue > 500)
     {
       lastSensorValue = 501;
       count++;
       Serial.println("rondje gedraaid");
     }
     yield();
  }
  return count;
}
