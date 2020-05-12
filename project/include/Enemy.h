#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
 public:
  explicit Enemy(float x, float y, int height, int weight, float hp, float dmg);
  void Update(float time, std::vector<Object> &obj) override;
  float GetDmg() const;
  void TakeDmg(float getDmg);
  float GetTimer() const;
  void ResetTimer();

 protected:
  float dmg;
  float hp;
  float timerHit;
};