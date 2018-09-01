#pragma once

#include "hue_cube.h"

class AngleLightMode : public LightMode
{
public:
  AngleLightMode(){};
  String name() { return "Angle"; };

  void setup();
  int loop();
};