#pragma once

#include "Entity.h"

class Bullet : public Entity {
 public:
  explicit Bullet(float x, float y, float dx, float dy, float dmg);
  void Update(float time, std::vector<Object> &obj) override;
  float GetDmg() const;
 private:
  float dmg;
};