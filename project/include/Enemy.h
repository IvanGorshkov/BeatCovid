#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"

class Enemy: public Entity {
 public:
  explicit Enemy(float x, float y, int height, int weight);
  void Update(float time, std::vector<Object> &obj) override;
  int GetDmg() const;
  void TakeDmg(int getDmg);
  float GetTimer() const;
  void ResetTimer();

 private:
  int dmg;
  int hp;
  float timerHit;
};