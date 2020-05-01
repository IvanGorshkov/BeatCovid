//
// Created by Ivan Gorshkov on 01.05.2020.
//

#include "Vaccine.h"

Vaccine::Vaccine(float x, float y, float w, float h):Entity(x,y,0,0,w,h) {
  sf::Texture tVaccine;
  tVaccine.loadFromFile("../files/images/vaccine.png");
  anim = AnimationManager(tVaccine);
  anim.Create("stay", 0, 0, 32, 32, 1, 0);
}

void Vaccine::Update(Player *player) {
  if (rect.intersects(player->GetRect())) {
    isLife = false;
  }
}
void Vaccine::Update(float time, std::vector<Object> &obj) {

}