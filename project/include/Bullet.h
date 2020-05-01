#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Entity.h"

class Bullet : public Entity {
 public:
  explicit Bullet(float x, float y, float dx, float dy, float dmg);
  void Update(float time, std::vector<Object> &obj) override;
  float GetDmg() const;
 private:
  float dmg;
};