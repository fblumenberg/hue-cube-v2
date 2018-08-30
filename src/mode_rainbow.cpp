#include <Arduino.h>

#include "hue_cube.h"
#include "mode_rainbow.h"

void RainbowLightMode::setup()
{
}

int RainbowLightMode::loop()
{
    cycle();

    for (uint16_t i = 0; i < NR_OF_LED; i++)
    {
        LED.set_crgb_at(i, leds[0]);
    }

    LED.sync();

    return 100; //delays between update
}

void RainbowLightMode::cycle()
{
    leds[0].SetHSV(h, sat, val);

    h += steps;
    if (h > 360)
    {
        h %= 360;
    }
}