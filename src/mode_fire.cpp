#include <Arduino.h>

#include "hue_cube.h"
#include "mode_fire.h"

void FireLightMode::flicker(cRGB *rgb)
{
    float f, rf, gf;

    f = random(64) - 20; // colors get brighter
    rf = random(16) - 8;
    gf = random(16) - 6; // yellows are more often
    rgb->r += rf + f;
    rgb->g += gf + f;

    // darker colors have more reds
    if (rgb->r <= r)
    {
        rgb->g = rgb->g - rgb->r / 2;
    }

    // bright colors flicker to darker colors
    rgb->r = rgb->r >= 254 ? 10 : (rgb->r <= 0 ? 0 : rgb->r);
    rgb->g = rgb->g >= 254 ? 10 : (rgb->g <= 0 ? 0 : rgb->g);

    // there is never a green flame (not even slightly)
    rgb->g = rgb->g > rgb->r ? rgb->r : rgb->g;
    // there is never a red flame (but a little is ok)
    rgb->r = rgb->r - 100 >= rgb->g ? rgb->r - 50 : rgb->r;
}

void FireLightMode::setup()
{
    s = 33;
    r = 120;
}

int FireLightMode::loop()
{
    if (abs(AcXf) > CHANGE_FACTOR)
    {
        r = r + (AcXf * (1.0 / CHANGE_FACTOR));
        r = r >= 180 ? 180 : r;
        r = r <= 0 ? 0 : r;
        delay(DEBOUNCE_DELAY); // debounce
    }

    if (abs(AcYf) > CHANGE_FACTOR)
    {
        s = s + (AcYf * (1.0 / CHANGE_FACTOR));
        s = s >= 1000 ? 1000 : s;
        s = s <= 10 ? 10 : s;
        delay(DEBOUNCE_DELAY); // debounce
    }

    int flickerLed = random(0, NR_OF_LED);
    flicker(&leds[flickerLed]);

    for (uint16_t i = 0; i < NR_OF_LED; i++)
    {
        LED.set_crgb_at(i, leds[i]);
    }

    LED.sync();

    return 1000 / s;
}