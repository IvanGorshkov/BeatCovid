#pragma once

#include "Enemy.h"

class Virus : public Enemy {
 public:
  void Update(float time, std::vector<Object> &obj) override;
  explicit Virus(float x, float y, int height, int weight);
};

