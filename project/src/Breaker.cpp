#include "Breaker.h"

Breaker::Breaker(float x, float y, int height, int weight)
  : Enemy(x, y, height, weight, 3, 1) {
  sf::Texture breakerTexture;
  breakerTexture.loadFromFile("../files/images/enemy.png");
  anim = AnimationManager(breakerTexture);
  anim.Create("move", 0, 0, 16, 16, 2, 0.002, 18);
  anim.Create("dead", 58, 0, 16, 16, 1, 0);
  anim.Set("move");
}

void Breaker::Update(float time, std::vector<Object> &obj) {
  timerHit += time;

  if (!isLife && !IsDie()) {
    timerDie += time;
  } else {
    if (hp < 0) {
      dx = 0;
      dy = 0;
      timerDie += time;
      anim.Set("dead");
      isLife = false;
    }
  }

  anim.Tick(time);
}