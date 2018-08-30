#pragma once

#define USE_HSV // enable hsv mode
#include "WS2812.h"

#define CHANGE_FACTOR 2400
#define DEBOUNCE_DELAY 66
#define MAX_BRIGHTNESS 64

const uint16_t NR_OF_LED = 5;
const int LED_PIN = 9;

extern cRGB leds[];

extern WS2812 LED;

// the MPU values for each module
extern int16_t AcX, AcY, AcZ, Temp, GyX, GyY, GyZ;
extern int16_t AcXf, AcYf, AcZf;

class LightMode
{
public:
  virtual void setup() = 0;
  virtual int loop() = 0;
};