//
// Created by Ivan Gorshkov on 02.05.2020.
//

#pragma once

#include "Entity.h"
class Arrmor: public Entity {
 public:
  Arrmor() = default;
  Arrmor(float x, float y, float w, float h);
  void Update(float time, std::vector<Object> &obj) override;
  void SetAnim(std::string name);
  void StatusAnim();
  void FlipAnim(bool value);
  int GetArm();
 protected:
  float arm;
};

