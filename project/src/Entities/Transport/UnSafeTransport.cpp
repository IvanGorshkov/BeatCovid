#include "UnSafeTransport.h"

UnSafeTransport::UnSafeTransport(float x, float y, int height, int weight, std::string name)
    : Transport(x, y, height, weight),
      name(name) {
  if (name == "bus") {
    setBus();
  }

  if (name == "metro") {
    setMetro();
  }
}

void UnSafeTransport::Update(float time, std::vector<Object> &obj) {
  if (isDrive && !isHitWall) {
    rect.left += dx * time;
    timerHit += time;
  }

  for (auto &i : obj) {
    if (i.rect.intersects(this->GetRect()) && i.name == "wall") {
      isHitWall = true;
    }

    if (i.rect.intersects(this->rect) && (i.name == "bus" || i.name == "metro")) {
      i.rect = this->rect;
    }
  }

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
  dmg = BUS_DMG;

  sf::Texture autoTexture;
  autoTexture.loadFromFile("../files/images/unSafe.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 0, 0, 145, 48, 1, 0);
  anim.Set("move");
}

void UnSafeTransport::setMetro() {
  dx = METRO_DX;
  dmg = METRO_DMG;

  sf::Texture autoTexture;
  autoTexture.loadFromFile("../files/images/unSafe.png");
  anim = AnimationManager(autoTexture);
  anim.Create("move", 0, 0, 145, 48, 1, 0);
  anim.Set("move");
}