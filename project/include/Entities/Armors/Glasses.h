#pragma once

#include "Armor.h"

class Glasses : public Armor {
 public:
  Glasses() = default;
  Glasses(float x, float y, float w, float h, int lvl);
};
