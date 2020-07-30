#include "Sick.h"
#include "ResourcePath.hpp"

Sick::Sick(float x, float y, float dx, float dy, int weight, int height)
    : Entity(x, y, 0, 0, weight, height),
      aliveAnimTimer(100),
      alive(false),
      end(false) {

  sf::Texture bulletTexture;
  bulletTexture.loadFromFile(resourcePath() + "files/images/ill.png");
  anim = AnimationManager(bulletTexture);
  anim.Create("ill", 2, 0, 75, 64, 3, 0.003, 79);
  anim.Create("alive", 1, 71, 90, 64, 3, 0.001, 94);
  anim.Set("ill");
}
void Sick::Update(float time, std::vector<Object> &obj) {
  anim.Tick(time);
  if (alive) {
    --aliveAnimTimer;
    if (aliveAnimTimer == 0) {
      end = true;
    }
  }
}

void Sick::SetAlive() {
  if (!alive) {
    anim.Set("alive");
    alive = true;
  }
}

bool Sick::GetEnd() const {
  return end;
}
