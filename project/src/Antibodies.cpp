//
// Created by Ivan Gorshkov on 01.05.2020.
//

#include "Antibodies.h"

Antibodies::Antibodies(float x, float y, float w, float h):Entity(x,y,0,0,w,h) {
  sf::Texture antibodiesTexture;
  antibodiesTexture.loadFromFile("../files/images/antitel.png");
  anim = AnimationManager(antibodiesTexture);
  anim.create("stay", 0, 0, 32, 32, 1, 0);
}

void Antibodies::Update(Player *player) {
  if (rect.intersects(player->getRect())) {
    isLife = false;
  }
}
void Antibodies::Update(float time, std::vector<Object> &obj) {

}