#pragma once

#include <vector>
#include "Entity.h"

#define ALIVE_ANIM_TIME

class Sick : public Entity {
 public:
  explicit Sick(float x, float y, float dx, float dy, int height, int weight);
  void Update(float time, std::vector<Object> &obj) override;
  void SetAlive();
  bool GetEnd() const;

 private:
  int aliveAnimTimer;
  bool alive;
  bool end;
};
