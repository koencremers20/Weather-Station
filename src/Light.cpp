#include "Light.h"

void setupLight()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void adjustRed(uint32_t redValue)
{
  analogWrite(redPin, redValue);
}
void adjustGreen(uint32_t greenValue)
{
  analogWrite(greenPin, greenValue);
}
void adjustBlue(uint32_t blueValue)
{
  analogWrite(bluePin, blueValue);
}
