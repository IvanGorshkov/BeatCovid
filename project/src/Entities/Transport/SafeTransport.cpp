#include "SafeTransport.h"

SafeTransport::SafeTransport(float x, float y, int height, int weight, const std::string &name)
    : Transport(x, y, height, weight),
      name(name) {
  if (name == "auto") {
    setAuto();
  }

  if (name == "monorail") {
    setMonorail();
  }
}

void SafeTransport::Update(float time, std::vector<Object> &obj) {
  if (isDrive && !isHitWall && fuel > 0) {
    rect.left += dx * time;
    fuel -= FUEL_LOSS;
  }

  for (auto &i : obj) {
    if (i.rect.intersects(this->rect) && i.name == "wall") {
      isHitWall = true;
    }

    if (i.rect.intersects(this->rect) && (i.name == "auto" || i.name == "monorail")) {
      i.rect = this->rect;
    }
  }

  anim.Tick(time);
}

void SafeTransport::setAuto() {
  dx = AUTO_DX;
  fuel = AUTO_FUEL;

  sf::Texture autoTexture;
  autoTexture.loadFromFile("../files/images/safe.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 0, 0, 129, 48, 1, 0);
  anim.Set("move");
}

void SafeTransport::setMonorail() {
  dx = MONORAIL_DX;
  fuel = MONORAIL_FUEL;

  sf::Texture autoTexture;
  autoTexture.loadFromFile("../files/images/safe.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 0, 0, 129, 48, 1, 0);
  anim.Set("move");
}
float SafeTransport::GetFuel() {
  return fuel;
}