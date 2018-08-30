#include <Arduino.h>

#include "hue_cube.h"

void tiltSetup()
{
}

static int16_t h = 0, s = 0, v = 60;
static float change;

int tiltLoop()
{

  if (abs(AcXf) > CHANGE_FACTOR)
  {
    h = h + (AcXf * (1.0 / CHANGE_FACTOR));
    h = h >= 360 ? 1 : h;
    h = h <= 0 ? 359 : h;
    delay(DEBOUNCE_DELAY); // debounce
  }

  if (abs(AcYf) > CHANGE_FACTOR)
  {
    s = s + (AcYf * (1.0 / CHANGE_FACTOR));
    s = s >= 254 ? 245 : s;
    s = s <= 10 ? 10 : s;
    delay(DEBOUNCE_DELAY); // debounce
  }

  v = MAX_BRIGHTNESS;

  leds[0].SetHSV(h, s, v);
  for (uint16_t i = 0; i < NR_OF_LED; i++)
  {
    LED.set_crgb_at(i, leds[0]);
  }

  LED.sync();

  return (1000 / 200);
}
