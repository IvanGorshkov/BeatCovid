#pragma once

#include "Level_map.h"
#include "Player.h"
#include "MusicManager.h"
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Enemy.h"
#include "Antibodies.h"
#include "GameLables.h"
#include "Police.h"
#include "OrdinaryEnemies.h"
#include "SafeTransport.h"
#include "UnSafeTransport.h"
#include "Sick.h"

class GameManager {
 public:
  explicit GameManager(Level &lvl, const std::vector<int> &arms, MusicManager &music, std::vector<int> stat, const std::vector<float> &config);
  // Обновление всех классов
  void Update(float time);
  // Вывод всех классов на экран
  void Draw(sf::RenderWindow &window);
  // Получение игрока
  std::shared_ptr<Player> GetPlayer();
  // Огонь игроком
  void Fire();
  // Садится в транспорт
  void TakeTransport();
  // Получение статистики
  std::vector<int> GetStat();

 private:
  MusicManager &music;

  std::vector<int> stat;
  int antigenPoints;

  std::vector<Object> obj;
  std::shared_ptr<Player> player;
  std::shared_ptr<Sick> sick;
  GameLables lables;

  // Методы работы с классом Bullet
  std::list<Bullet> playerBullets;
  std::list<Bullet>::iterator playerBulletsIt;
  std::list<Bullet> enemyBullets;
  std::list<Bullet>::iterator enemyBulletsIt;
  void updateBullet(float time);
  void drawBullet(sf::RenderWindow &window);
  void checkHitEnemy();
  void checkHitPlayer();
  void bulletPlayer();

  // Методы работы с классом Enemy
  std::list<std::shared_ptr<Enemy>> enemies;
  std::list<std::shared_ptr<Enemy>>::iterator enemiesIt;
  void updateEnemy(float time);
  void drawEnemy(sf::RenderWindow &window);

  // Методы работы с классом Antibodies
  std::list<Antibodies> antibodies;
  std::list<Antibodies>::iterator antibodiesIt;
  void drawAntibodies(sf::RenderWindow &window);
  void updateAntibodies();

  // Методы работы с классом Transport
  std::list<SafeTransport> safeTransports;
  std::list<SafeTransport>::iterator safeTransportsIt;
  std::list<UnSafeTransport> unSafeTransports;
  std::list<UnSafeTransport>::iterator unSafeTransportsIt;
  void updateTransport(float time);
  void updateSafeTransport(float time);
  void updateUnSafeTransport(float time);
  void drawTransport(sf::RenderWindow &window);
  void drawSafeTransport(sf::RenderWindow &window);
  void drawUnSafeTransport(sf::RenderWindow &window);
};
