#pragma once

#include "Entity.h"

class Enemy : public Entity {
 public:
  explicit Enemy(float x, float y, int height, int weight, float hp, float dmg);
  explicit Enemy(float x, float y, int height, int weight);
  void SetHpGmg(float getHp, float getDmg);
  void Update(float time, std::vector<Object> &obj) override;
  float GetDmg() const;
  void TakeDmg(float getDmg);
  float GetTimer() const;
  void ResetTimer();
  void SetFire(bool fire);
  void SetDir(bool dir);

 protected:
  bool  fire;
  bool dir;
  float dmg;
  float hp;
  float timerHit;
};