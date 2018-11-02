#ifndef Light_H
#define Light_H

#include <stdint.h>
#include <Arduino.h>

#define redPin D4
#define greenPin D5
#define bluePin D6

void setupLight();
void adjustRed(uint32_t redValue);
void adjustGreen(uint32_t greenValue);
void adjustBlue(uint32_t blueValue);

#endif
