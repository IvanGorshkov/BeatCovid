#include "Bullet.h"

Bullet::Bullet(float x, float y, float dx, float dy, int dmg)
    : Entity(x, y, dx, dy, 16, 16), dmg(dmg) {
  sf::Texture bulletTexture;
  bulletTexture.loadFromFile("../files/images/bullet.png");
  anim = AnimationManager(bulletTexture);
  anim.create("move", 7, 10, 8, 8, 1, 0);
  anim.create("explode", 27, 7, 18, 18, 4, 0.01, 29);
  anim.set("move");
}

void Bullet::Update(float time, std::vector<Object> &obj) {
  if (!isLife && !IsDie()) {
    timerDie += time;
  } else {
    for (auto &i : obj) {
      if (rect.intersects(i.rect)) {
        dx = 0;
        dy = 0;
        timerDie += time;
        anim.set("explode");
        isLife = false;
        break;
      }
    }
  }

  rect.left += dx * time;
  rect.top += dy * time;

  anim.tick(time);
}

int Bullet::GetDmg() const {
  return dmg;
}
