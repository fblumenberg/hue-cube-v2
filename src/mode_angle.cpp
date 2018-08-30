#include <Arduino.h>

#include "mode_angle.h"

void AngleLightMode::setup()
{
}

int AngleLightMode::loop()
{

  // Tmp/340.00+36.53  //equation for temperature in degrees C from datasheet

  leds[0].r = abs(AcX) >= 32768 / 2 ? MAX_BRIGHTNESS : map(abs(AcX), 0, 32768 / 2, 0, MAX_BRIGHTNESS);
  leds[0].g = abs(AcY) >= 32768 / 2 ? MAX_BRIGHTNESS : map(abs(AcY), 0, 32768 / 2, 0, MAX_BRIGHTNESS);
  leds[0].b = abs(AcZ) >= 32768 / 2 ? MAX_BRIGHTNESS : map(abs(AcZ), 0, 32768 / 2, 0, MAX_BRIGHTNESS);

  for (uint16_t i = 0; i < NR_OF_LED; i++)
  {
    LED.set_crgb_at(i, leds[0]);
  }

  LED.sync();

  return (1000 / 100);
}
