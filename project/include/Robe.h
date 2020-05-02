//
// Created by Ivan Gorshkov on 02.05.2020.
//

#pragma once

#include "Arrmor.h"

class Robe: public Arrmor {
 public:
  Robe() = default;
  Robe(float x, float y, float w, float h, int lvl);
};
