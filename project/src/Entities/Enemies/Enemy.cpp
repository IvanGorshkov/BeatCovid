#include "Enemy.h"

Enemy::Enemy(float x, float y, int height, int weight, float hp, float dmg)
    : Entity(x, y, 0, 0, height, weight),
      hp(hp),
      dmg(dmg),
      timerHit(0),
      fire(false),
      dir(false),
      dieSound(false) {
}

Enemy::Enemy(float x, float y, int height, int weight)
    : Entity(x, y, 0, 0, height, weight),
      timerHit(0) {
}

void Enemy::SetHpGmg(float getHp, float getDmg) {
  hp = getHp;
  dmg = getDmg;
}

void Enemy::Update(float time, std::vector<Object> &obj) {
  timerHit += time;
  if (fire) {
    anim.Set("fire");
  } else {
    anim.Set("move");
  }

  if (!isLife) {
    anim.Set("dead");
  }

  if (hp < 0 && isLife) {
    dx = 0;
    dy = 0;
    anim.Set("dead");
    isLife = false;
    dieSound = true;
  }

  anim.Flip(dir);
  anim.Tick(time);
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

void Enemy::SetFire(bool getFire) {
  this->fire = getFire;
}

void Enemy::SetDir(bool getDir) {
  this->dir = getDir;
}

bool Enemy::GetDieSound() const {
  return dieSound;
}

void Enemy::SetDieSound() {
  dieSound = false;
}

