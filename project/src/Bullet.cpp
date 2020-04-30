#include "Bullet.h"

Bullet::Bullet(float x, float y, float dx, float dy)
    : Entity(x, y, dx, dy, 16, 16) {
  sf::Texture bulletTexture;
  bulletTexture.loadFromFile("../bullet.png");
  anim = AnimationManager(bulletTexture);
  anim.create("move", 7, 10, 8, 8, 1, 0);
  anim.create("explode", 27, 7, 18, 18, 4, 0.01, 29);
  anim.set("move");
}

void Bullet::Update(float time, std::vector<Object> &obj) {
  rect.left += dx * time;
  rect.top += dy * time;

  for (auto &i : obj) {
    if (rect.intersects(i.rect) && i.name == "wall") {
      dx = 0;
      dy = 0;
      isLife = false;
      anim.set("explode");
    }
  }

  anim.tick(time);
}
