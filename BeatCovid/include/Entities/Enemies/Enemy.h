#pragma once

#include <vector>
#include <string>
#include "Entity.h"

#define ENEMY_HIT_TIME 1500

class Enemy : public Entity {
 public:
  explicit Enemy(float x, float y, int height, int weight, float hp, float dmg, std::string name);
  explicit Enemy(float x, float y, int height, int weight, std::string name);
  void SetHpGmg(float getHp, float getDmg);
  void Update(float time, std::vector<Object> &obj) override;
  float GetDmg() const;
  void TakeDmg(float getDmg);
  float GetTimer() const;
  void ResetTimer();
  void SetFire(bool getFire);
  void SetDir(bool getDir);
  bool GetDieSound() const;
  void SetDieSound();
  std::string GetName();

 protected:
  std::string name;
  bool dieSound;
  bool fire;
  bool dir;
  float dmg;
  float hp;
  float timerHit;
};
