#pragma once

#include "Enemy.h"

#define BREAKER_HP 3
#define BREAKER_DMG 1
#define DELIVERY_HP 3
#define DELIVERY_DMG 1
#define VIRUS_HP 3
#define VIRUS_DMG 1

class OrdinaryEnemies : public Enemy {
 public:
  explicit OrdinaryEnemies(float x, float y, int height, int weight, const std::string &name, std::vector<float> config);

 private:
  std::vector<float> config;
  void setBreaker();
  void setDelivery();
  void setVirus();
};