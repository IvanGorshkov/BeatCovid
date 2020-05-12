#pragma once

#include "Enemy.h"

class Virus : public Enemy {
 public:
  explicit Virus(float x, float y, int height, int weight);
  void Update(float time, std::vector<Object> &obj) override;
};

