#include "Bullet.h"

Bullet::Bullet(float x, float y, float dx, float dy, float dmg)
    : Entity(x, y, dx, dy, 16, 16), dmg(dmg),
      timerDie(0),
      isDie(false) {
  sf::Texture bulletTexture;
  bulletTexture.loadFromFile("../files/images/bullet.png");
  anim = AnimationManager(bulletTexture);
  anim.Create("move", 7, 10, 8, 8, 1, 0);
  anim.Create("explode", 27, 7, 18, 18, 4, 0.01, 29);
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