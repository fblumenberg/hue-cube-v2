#pragma once

#include "hue_cube.h"

class AngleLightMode : public LightMode
{
public:
  AngleLightMode(){};

  void setup();
  int loop();
};