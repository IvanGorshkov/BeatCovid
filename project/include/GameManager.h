#pragma once

#include "Level_map.h"

#include "Player.h"
#include <list>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bullet.h"

class GameManager {
 public:
  explicit GameManager(Level &lvl);
  void Update(float time);
  void Draw(sf::RenderWindow &window);
  Player *GetPlayer();
  void Fire();

 private:
  void addBullet(float x, float y, float dx, float dy);
  std::vector<Object> obj;
  std::list<Entity *> entities;
  std::list<Entity *>::iterator it;
  Player *player;
//  BulletManager bullets;
};