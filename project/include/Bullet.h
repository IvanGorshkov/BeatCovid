#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Entity.h"

#define BLOKSIZE 16

class Bullet : public Entity {
 public:
  explicit Bullet(float x, float y, float dx, float dy);
  void Update(float time, std::vector<Object> &obj) override;
};