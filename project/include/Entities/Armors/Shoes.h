#pragma once

#include "Armor.h"

class Shoes : public Armor {
 public:
  Shoes() = default;
  Shoes(float x, float y, float w, float h, int lvl);
};
