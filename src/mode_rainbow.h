#pragma once

#include "hue_cube.h"

class RainbowLightMode : public LightMode
{
    int h = 0;       //stores 0 to 614
    byte steps = 15; //number of hues we skip in a 360 range per update

    byte sat = 255;
    byte val = 127;

    void cycle();

  public:
    RainbowLightMode(){};

    void setup();
    int loop();
};