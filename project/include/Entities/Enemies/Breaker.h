#pragma once

#include "Enemy.h"

class Breaker : public Enemy {
 public:
  explicit Breaker(float x, float y, int height, int weight);
  void Update(float time, std::vector<Object> &obj) override;
};