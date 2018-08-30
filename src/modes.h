#pragma once

#include "hue_cube.h"

enum Mode
{
    Fire = 0,
    Tilt,
    Angle,
    Rainbow,
    LastMode
};

void setupModes();
LightMode *activeLightMode();
LightMode *nextLightMode();