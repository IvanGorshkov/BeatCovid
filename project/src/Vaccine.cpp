//
// Created by Ivan Gorshkov on 01.05.2020.
//

#include "Vaccine.h"

Vaccine::Vaccine(float x, float y, float w, float h):Entity(x,y,0,0,w,h) {
  sf::Texture tVaccine;
  tVaccine.loadFromFile("../vaccine.png");
  anim = AnimationManager(tVaccine);
  anim.create("stay", 0, 0, 32, 32, 1, 0);
}

void Vaccine::Update(Player *player) {
  if (rect.intersects(player->getRect())) {
    isLife = false;
  }
}
void Vaccine::Update(float time, std::vector<Object> &obj) {

}