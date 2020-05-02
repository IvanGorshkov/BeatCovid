//
// Created by Ivan Gorshkov on 02.05.2020.
//

#include "Arrmor.h"

Arrmor::Arrmor(float x, float y, float w, float h): Entity(x, y, 0, 0, w, h) {

}

void Arrmor::Update(float time, std::vector<Object> &obj) {
  anim.Tick(time);
  rect = obj[0].rect;
}

void Arrmor::SetAnim(std::string name) {
  anim.Set(name);
}

void Arrmor::StatusAnim() {
  anim.Pause();
}

void Arrmor::FlipAnim(bool value) {
  anim.Flip(value);
}

int Arrmor::GetArm(){
  return arm;
}
