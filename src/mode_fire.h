#pragma once

#include "hue_cube.h"

class FireLightMode : public LightMode
{
  int16_t s; // anim speed
  int16_t r; // amount of red

  void flicker(cRGB *rgb);

public:
  FireLightMode(){};

  void setup();
  int loop();
};