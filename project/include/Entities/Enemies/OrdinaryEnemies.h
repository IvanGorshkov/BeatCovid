#pragma once

#include <vector>
#include <string>
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
  void setBreaker(float hp, float dmg);
  void setDelivery(float hp, float dmg);
  void setVirus(float hp, float dmg);
};
