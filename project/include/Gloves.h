//
// Created by Ivan Gorshkov on 02.05.2020.
//

#pragma once

#include "Arrmor.h"

class Gloves: public Arrmor {
 public:
  Gloves() = default;
  Gloves(float x, float y, float w, float h, int lvl);
};
