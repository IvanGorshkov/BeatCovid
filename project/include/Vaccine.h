//
// Created by Ivan Gorshkov on 01.05.2020.
//

#pragma once

#include "Entity.h"
#include "Player.h"

class Vaccine: public Entity  {
 public:
  Vaccine(float x, float y, float w, float h);
  void Update(Player *player);
  void Update(float time, std::vector<Object> &obj) override;
};
