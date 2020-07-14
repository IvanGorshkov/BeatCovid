#include "UnSafeTransport.h"
#include "ResourcePath.hpp"

UnSafeTransport::UnSafeTransport(float x, float y, int height, int weight, const std::string &name, std::vector<float> config)
    : Transport(x, y, height, weight, name) {
  if (name == "bus") {
    setBus(config[13]);
  }

  if (name == "metro") {
    setMetro(config[14]);
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

void UnSafeTransport::setBus(float getDmg) {
  dx = BUS_DX;
  dmg = getDmg;

  sf::Texture autoTexture;
  autoTexture.loadFromFile(resourcePath() + "files/images/bus.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 4, 4, 393, 100, 2, 0.005, 397);
  anim.Set("move");
}

void UnSafeTransport::setMetro(float getDmg) {
  dx = METRO_DX;
  dmg = getDmg;

  sf::Texture autoTexture;
  autoTexture.loadFromFile(resourcePath() + "files/images/metro.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 64, 2, 924, 140, 2, 0.002, 994);
  anim.Set("move");
}
