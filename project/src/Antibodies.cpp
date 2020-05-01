#include "Antibodies.h"

Antibodies::Antibodies(float x, float y, float w, float h):Entity(x,y,0,0,w,h) {
  sf::Texture antibodiesTexture;
  antibodiesTexture.loadFromFile("../files/images/antitel.png");
  anim = AnimationManager(antibodiesTexture);
  anim.Create("stay", 0, 0, 32, 32, 1, 0);
}

void Antibodies::Update(Player *player) {
  if (rect.intersects(player->GetRect())) {
    isLife = false;
  }
}
void Antibodies::Update(float time, std::vector<Object> &obj) {

}