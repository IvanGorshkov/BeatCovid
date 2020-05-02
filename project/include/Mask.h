//
// Created by Ivan Gorshkov on 02.05.2020.
//

#pragma once

#include "Arrmor.h"

class Mask: public Arrmor {
 public:
  Mask() = default;
  Mask(float x, float y, float w, float h, int lvl);
};
