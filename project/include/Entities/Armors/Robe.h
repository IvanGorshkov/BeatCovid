#pragma once

#include "Armor.h"

class Robe : public Armor {
 public:
  Robe() = default;
  Robe(float x, float y, float w, float h, int lvl);
};
