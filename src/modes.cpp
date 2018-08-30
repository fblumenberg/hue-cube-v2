#include <Arduino.h>

#include "modes.h"
#include "mode_fire.h"
#include "mode_angle.h"
#include "mode_tilt.h"
#include "mode_rainbow.h"

static int currentMode = Fire;

static FireLightMode fireMode;
static FireLightMode tiltMode;
static FireLightMode angleMode;
static FireLightMode rainbowMode;

static LightMode *modes[] = {
    &fireMode,
    &tiltMode,
    &angleMode,
    &rainbowMode,
};

void setupModes()
{
    for (int m = Fire; m < LastMode; m++)
    {
        modes[m]->setup();
    }
}

LightMode *activeLightMode()
{
    return modes[currentMode];
}

LightMode *nextLightMode()
{
    currentMode++;
    if (currentMode == LastMode)
        currentMode = Fire;

    return modes[currentMode];
}
