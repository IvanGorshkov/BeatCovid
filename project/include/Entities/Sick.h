//
// Created by Ivan Gorshkov on 28.05.2020.
//

#pragma once

#include "Entity.h"
class Sick: public Entity {
 public:
  explicit Sick(float x, float y, float dx, float dy, int height, int weight);
  void Update(float time, std::vector<Object> &obj) override;
  void SetAlive();
  bool GetEnd();
 private:
  int aliveC;
  bool alive;
  bool end;
};
