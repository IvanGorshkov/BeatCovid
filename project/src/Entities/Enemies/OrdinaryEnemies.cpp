#include "OrdinaryEnemies.h"

OrdinaryEnemies::OrdinaryEnemies(float x, float y, int height, int weight, const std::string &name)
    : Enemy(x, y, height, weight),
      name(name) {
  if (name == "breaker") {
    setBreaker();
  }

  if (name == "delivery") {
    setDelivery();
  }

  if (name == "virus") {
    setVirus();
  }
}

void OrdinaryEnemies::setBreaker() {
  SetHpGmg(BREAKER_HP, BREAKER_DMG);
  sf::Texture breakerTexture;
  breakerTexture.loadFromFile("../files/images/breaker.png");
  anim = AnimationManager(breakerTexture);
  anim.Create("move", 4, 4, 64, 64, 6, 0.002, 72);
  anim.Create("fire", 68, 72, 64, 64, 2, 0.004, 72);
  anim.Create("dead", 4, 148, 64, 64, 3, 0.002, 72);
  anim.Set("move");
}

void OrdinaryEnemies::setDelivery() {
  SetHpGmg(DELIVERY_HP, DELIVERY_DMG);
  sf::Texture deliveryTexture;
  deliveryTexture.loadFromFile("../files/images/delivery.png");
  anim = AnimationManager(deliveryTexture);
  anim.Create("move", 4, 4, 64, 64, 4, 0.002, 72);
  anim.Create("fire", 4, 72, 64, 64, 4, 0.004, 72);
  anim.Create("dead", 4, 148, 64, 64, 3, 0.002, 72);
  anim.Set("move");
}

void OrdinaryEnemies::setVirus() {
  SetHpGmg(VIRUS_HP, VIRUS_DMG);
  sf::Texture virusTexture;
  virusTexture.loadFromFile("../files/images/virus.png");
  anim = AnimationManager(virusTexture);
  anim.Create("move", 4, 4, 64, 64, 4, 0.002, 72);
  anim.Create("fire", 4, 72, 64, 64, 3, 0.004, 72);
  anim.Create("dead", 4, 148, 64, 64, 2, 0.002, 72);
  anim.Set("move");
}