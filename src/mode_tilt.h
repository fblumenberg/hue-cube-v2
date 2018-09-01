#pragma once

#include "hue_cube.h"

class TiltLightMode : public LightMode
{
  int16_t h = 0, s = 0, v = 60;

public:
  TiltLightMode(){};
  String name() { return "Tilt"; };

  void setup();
  int loop();
};