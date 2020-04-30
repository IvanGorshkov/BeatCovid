#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"

class Enemy: public Entity {
 public:
  explicit Enemy(float x, float y, int height, int weight);
  void Update(float time, std::vector<Object> &obj) override;

 private:
  int dmg;
  int countDmg;
};

//class Police : public Enemy {
// public:
//  Police(int x, int y);
//};
//
//class Delivery : public Enemy {
// public:
//  Delivery(int x, int y);
//};
//
//class Breaker : public Enemy {
// public:
//  Breaker(int x, int y);
//};
//
//class Virus : public Enemy {
// public:
//  Virus(int x, int y);
//};
