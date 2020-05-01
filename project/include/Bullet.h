#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Entity.h"

class Bullet : public Entity {
 public:
  explicit Bullet(float x, float y, float dx, float dy, int dmg);
  void Update(float time, std::vector<Object> &obj) override;
  int GetDmg() const;
 private:
  int dmg;
};