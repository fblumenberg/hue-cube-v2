#include <Arduino.h>

#include "modes.h"
#include "mode_fire.h"
#include "mode_angle.h"
#include "mode_tilt.h"
#include "mode_rainbow.h"

static int currentMode = Rainbow;

static FireLightMode fireMode;
static TiltLightMode tiltMode;
static AngleLightMode angleMode;
static RainbowLightMode rainbowMode;

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
        Serial.print("Setup ");
        Serial.print(m);
        Serial.println(modes[m]->name());
        modes[m]->setup();
    }
}

LightMode *activeLightMode()
{
    return modes[currentMode];
}

LightMode *nextLightMode()
{
    Serial.print("Current mode ");
    Serial.println(currentMode);
    currentMode++;
    if (currentMode == LastMode)
        currentMode = Fire;
    Serial.print("Current mode ");
    Serial.println(currentMode);

    LightMode *m = modes[currentMode];
    Serial.print((unsigned long)m);
    Serial.println(m->name());

    return m;
}
