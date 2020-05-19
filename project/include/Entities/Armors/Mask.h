#pragma once

#include "Armor.h"

class Mask : public Armor {
 public:
  Mask() = default;
  Mask(float x, float y, float w, float h, int lvl);
};
