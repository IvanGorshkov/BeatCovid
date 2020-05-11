#pragma once

#include "Arrmor.h"

class Robe : public Arrmor {
 public:
  Robe() = default;
  Robe(float x, float y, float w, float h, int lvl);
};
