#include "Armor.h"

Armor::Armor(float x, float y, float w, float h) : Entity(x, y, 0, 0, w, h) {

}

void Armor::Update(float time, std::vector<Object> &obj) {
  anim.Tick(time);
  rect = obj[0].rect;
}

void Armor::SetAnim(const std::string& name) {
  anim.Set(name);
}

void Armor::StatusAnim() {
  anim.Pause();
}

void Armor::FlipAnim(bool value) {
  anim.Flip(value);
}

int Armor::GetArm() const {
  return arm;
}
