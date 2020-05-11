#pragma once

#include "Arrmor.h"

class Glasses : public Arrmor {
 public:
  Glasses() = default;
  Glasses(float x, float y, float w, float h, int lvl);
};
