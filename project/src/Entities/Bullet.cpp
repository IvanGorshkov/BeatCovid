#include "Bullet.h"

Bullet::Bullet(float x, float y, float dx, float dy, float dmg, bool player)
    : Entity(x, y, dx, dy, 16, 16), dmg(dmg),
      timerDie(0),
      isDie(false) {

  sf::Texture bulletTexture;
  bulletTexture.loadFromFile("../files/images/bullets.png");
  anim = AnimationManager(bulletTexture);
  if (player) {
    anim.Create("move", 8, 50, 30, 30, 1, 0);
    anim.Create("explode", 38, 50, 30, 30, 3, 0.01, 34);
  } else {
    anim.Create("move", 8, 8, 30, 30, 1, 0);
    anim.Create("explode", 38, 8, 30, 30, 3, 0.01, 34);
  }
  anim.Set("move");
}

void Bullet::Update(float time, std::vector<Object> &obj) {
  if (!isLife && !IsDie()) {
    timerDie += time;
  } else {
    for (auto &i : obj) {
      if (rect.intersects(i.rect) && !(i.name == "vaccine" || i.name == "antigen")) {
        dx = 0;
        dy = 0;
        timerDie += time;
        anim.Set("explode");
        isLife = false;
        break;
      }
    }
  }

  rect.left += dx * time;
  rect.top += dy * time;

  anim.Tick(time);
}

float Bullet::GetDmg() const {
  return dmg;
}

bool Bullet::IsDie() {
  if (timerDie > BULLET_TIME_DIE) {
    isDie = true;
  }

  return isDie;
}