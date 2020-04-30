#pragma once

#include "Bullet.h"
#include "Level_map.h"
#include "AnimationManager.h"
#include <list>

class BulletManager {
 public:
  explicit BulletManager();
  void update(float tim);
  void add(float x, float y, float dx, float dy);
  void draw(sf::RenderWindow &window);

 private:
  std::list<Bullet> bullets;
  std::list<Bullet>::iterator it;
};

