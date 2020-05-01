#pragma once

#include "Level_map.h"
#include "Player.h"
#include <list>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Antibodies.h"
#include "GameLables.h"
#include "Vaccine.h"

class GameManager {
 public:
  explicit GameManager(Level &lvl);
  void Update(float time);
  void Draw(sf::RenderWindow &window);
  Player *GetPlayer();
  void Fire();

 private:
  void updateBullet(float time);
  void drawBullet(sf::RenderWindow &window);
  void updateEnemy(float time);
  void drawEnemy(sf::RenderWindow &window);
  void drawAntibodies(sf::RenderWindow &window);
  void updateAntibodies(float time);
  void drawVaccine(sf::RenderWindow &window);
  void updateVaccine(float time);
  void dieEnemy();
  void hitPlayer();
  void diePlayer();
  std::vector<Object> obj;
  std::list<Bullet> playerBullets;
  std::list<Bullet>::iterator playerBulletsIt;
  std::list<Bullet> enemyBullets;
  std::list<Bullet>::iterator enemyBulletsIt;
  std::list<Enemy> enemies;
  std::list<Enemy>::iterator enemiesIt;
  std::list<Antibodies> antibodies;
  std::list<Antibodies>::iterator antibodiesIt;
  std::list<Vaccine> vaccine;
  std::list<Vaccine>::iterator vaccineIt;
  Player *player;
  GameLables lables;
};