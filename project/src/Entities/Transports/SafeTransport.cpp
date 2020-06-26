#include "SafeTransport.h"

#include <utility>

SafeTransport::SafeTransport(float x, float y, int height, int weight, const std::string &name, std::vector<float> config)
    : Transport(x, y, height, weight, name),
    config(std::move(config)) {

  if (name == "auto") {
    setAuto();
  }

  if (name == "monorail") {
    setMonorail();
  }
}

void SafeTransport::Update(float time, std::vector<Object> &obj) {
  if (isDrive && !isHitWall && fuel > 0) {
    if (!dir) {
      rect.left += dx * time;
    } else {
      rect.left -= dx * time;
    }

    fuel -= FUEL_LOSS;
  }

  for (auto &i : obj) {
    if (i.rect.intersects(this->rect) && i.name == "wall" && isDrive) {
      isHitWall = true;
    }

    if (i.rect.intersects(this->rect) && (i.name == "auto" || i.name == "monorail")) {
      i.rect = this->rect;
    }
  }

  anim.Flip(dir);
  anim.Tick(time);
}

void SafeTransport::setAuto() {
  dx = AUTO_DX;
  fuel = config[11];

  sf::Texture autoTexture;
  autoTexture.loadFromFile(FILES_PATH"files/images/safe.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 4, 5, 200, 100, 2, 0.005, 204);
  anim.Set("move");
}

void SafeTransport::setMonorail() {
  dx = MONORAIL_DX;
  fuel = config[12];

  sf::Texture autoTexture;
  autoTexture.loadFromFile(FILES_PATH"files/images/mono.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 39, 2, 976, 140, 2, 0.002, 986);
  anim.Set("move");
}
float SafeTransport::GetFuel() const {
  return fuel;
}
