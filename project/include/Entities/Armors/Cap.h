#pragma once

#include "Armor.h"

class Cap : public Armor {
 public:
  Cap() = default;
  Cap(float x, float y, float w, float h, int lvl);
};
