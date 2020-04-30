#pragma once

#include "Level_map.h"
#include "Player.h"
#include <list>
#include <SFML/Graphics.hpp>
#include "BulletManager.h"

class GameManager {
 public:
  explicit GameManager(Level &lvl);
  void Update(float time);
  void draw(sf::RenderWindow &window);
  Player *GetPlayer();
  void Fire();

 private:
  std::vector<Object> obj;
  Player *player;
  BulletManager bullets;
};