#include "Enemy.h"

Enemy::Enemy(float x, float y,int height, int weight)
    : Entity(x, y, 0, 0, height, weight),
    hp(3),
    dmg(1),
    timerHit(0) {
  sf::Texture enemyTexture;
  enemyTexture.loadFromFile("../files/images/enemy.png");
  anim = AnimationManager(enemyTexture);
  anim.create("move", 0, 0, 16, 16, 2, 0.002, 18);
  anim.create("dead", 58, 0, 16, 16, 1, 0);
  anim.set("move");
}

void Enemy::Update(float time, std::vector<Object> &obj) {
  timerHit += time;

  if (!isLife && !IsDie()) {
    timerDie += time;
  } else {
    if (hp < 0) {
      dx = 0;
      dy = 0;
      timerDie += time;
      anim.set("dead");
      isLife = false;
    }
  }

  anim.tick(time);
}

float Enemy::GetTimer() const {
  return timerHit;
}

void Enemy::ResetTimer() {
  timerHit = 0;
}

int Enemy::GetDmg() const {
  return dmg;
}

void Enemy::TakeDmg(int getDmg) {
  hp -= getDmg;
}
