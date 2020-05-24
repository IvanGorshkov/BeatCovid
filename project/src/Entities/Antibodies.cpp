#include "Antibodies.h"

Antibodies::Antibodies(float x, float y, float w, float h, const std::string &name)
    : Entity(x, y, 0, 0, w, h),
      name(name) {
  if (name == "antigen") {
    setAntigen();
  }

  if (name == "vaccine") {
    setVaccine();
  }
}

void Antibodies::Update(Player *player) {
  anim.Tick(0.05);
  if (rect.intersects(player->GetRect())) {
    isLife = false;
  }
}

void Antibodies::Update(float time, std::vector<Object> &obj) {

}

std::string Antibodies::GetName() {
  return name;
}

void Antibodies::setAntigen() {
  sf::Texture antigenTexture;
  antigenTexture.loadFromFile("../files/images/antitel.png");
  anim = AnimationManager(antigenTexture);
  anim.Create("stay", 4, 4, 32, 32, 3, 1, 34);
  anim.Set("stay");
}
void Antibodies::setVaccine() {
  sf::Texture vaccineTexture;
  vaccineTexture.loadFromFile("../files/images/vaccine.png");
  anim = AnimationManager(vaccineTexture);
  anim.Create("stay", 4, 4, 32, 32, 3, 1, 34);
  anim.Set("stay");
}