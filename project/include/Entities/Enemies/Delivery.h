#pragma once

#include "Enemy.h"

class Delivery : public Enemy {
 public:
  void Update(float time, std::vector<Object> &obj) override;
  explicit Delivery(float x, float y, int height, int weight);
};

