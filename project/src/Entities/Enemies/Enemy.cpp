#include "Enemy.h"

Enemy::Enemy(float x, float y, int height, int weight, float hp, float dmg)
    : Entity(x, y, 0, 0, height, weight),
      hp(hp),
      dmg(dmg),
      timerHit(0) {
}

void Enemy::Update(float time, std::vector<Object> &obj) {
//  timerHit += time;
//
//  if (!isLife && !IsDie()) {
//    timerDie += time;
//  } else {
//    if (hp < 0) {
//      dx = 0;
//      dy = 0;
//      timerDie += time;
//      anim.Set("dead");
//      isLife = false;
//    }
//  }
//
//  anim.Tick(time);
}

float Enemy::GetTimer() const {
  return timerHit;
}

void Enemy::ResetTimer() {
  timerHit = 0;
}

float Enemy::GetDmg() const {
  return dmg;
}

void Enemy::TakeDmg(float getDmg) {
  hp -= getDmg;
}
