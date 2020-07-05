#include "UnSafeTransport.h"
#include <utility>

UnSafeTransport::UnSafeTransport(float x, float y, int height, int weight, const std::string &name, std::vector<float> config)
    : Transport(x, y, height, weight, name),
    config(std::move(config)) {

  if (name == "bus") {
    setBus();
  }

  if (name == "metro") {
    setMetro();
  }
}

void UnSafeTransport::Update(float time, std::vector<Object> &obj) {
  if (isDrive && !isHitWall) {
    if (!dir) {
      rect.left += dx * time;
    } else {
      rect.left -= dx * time;
    }

    timerHit += time;
  }

  for (auto &i : obj) {
    if (i.rect.intersects(this->GetRect()) && i.name == "wall" && isDrive) {
      isHitWall = true;
    }

    if (i.rect.intersects(this->rect) && (i.name == "bus" || i.name == "metro")) {
      i.rect = this->rect;
    }
  }

  anim.Flip(dir);
  anim.Tick(time);
}

float UnSafeTransport::GetDmg() {
  if (timerHit > HP_TIME_LOSS) {
    timerHit = 0;
    return dmg;
  }

  return 0;
}

float UnSafeTransport::PrintDmg() const {
  return dmg;
}

void UnSafeTransport::setBus() {
  dx = BUS_DX;
  dmg = config[13];

  sf::Texture autoTexture;
  autoTexture.loadFromFile(FILES_PATH"files/images/bus.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 4, 4, 393, 100, 2, 0.005, 397);
  anim.Set("move");
}

void UnSafeTransport::setMetro() {
  dx = METRO_DX;
  dmg = config[14];

  sf::Texture autoTexture;
  autoTexture.loadFromFile(FILES_PATH"files/images/metro.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 64, 2, 924, 140, 2, 0.002, 994);
  anim.Set("move");
}
