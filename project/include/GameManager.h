#pragma once

#include "Level_map.h"
#include "Player.h"
#include <list>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bullet.h"
#include "Enemy.h"

class GameManager {
 public:
  explicit GameManager(Level &lvl);
  void Update(float time);
  void Draw(sf::RenderWindow &window);
  Player *GetPlayer();
  void Fire();

 private:
  void addBullet(float x, float y, float dx, float dy);
  void updateBullet(float time);
  void drawBullet(sf::RenderWindow &window);
  void updateEnemy(float time);
  void drawEnemy(sf::RenderWindow &window);
  void hitPlayer();
  std::vector<Object> obj;
  std::list<Bullet> bullets;
  std::list<Bullet>::iterator bulletsIt;
  std::list<Enemy> enemies;
  std::list<Enemy>::iterator enemiesIt;
  Player *player;
};