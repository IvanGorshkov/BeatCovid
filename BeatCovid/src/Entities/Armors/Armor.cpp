#include "Armor.h"

Armor::Armor(float x, float y, float w, float h, int lvl)
    : Entity(x, y, 0, 0, w, h),
      lvl(lvl) {
}

void Armor::Update(float time, std::vector<Object> &obj) {
  anim.Tick(time);
  rect = obj[0].rect;
}

void Armor::SetAnim(const std::string &name) {
  anim.Set(name);
}

void Armor::FlipAnim(bool value) {
  anim.Flip(value);
}

int Armor::GetArm() const {
  return arm;
}

int Armor::Getlvl() const {
  return lvl;
}
