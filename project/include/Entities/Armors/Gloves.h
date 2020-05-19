#pragma once

#include "Armor.h"

class Gloves : public Armor {
 public:
  Gloves() = default;
  Gloves(float x, float y, float w, float h, int lvl);
};
