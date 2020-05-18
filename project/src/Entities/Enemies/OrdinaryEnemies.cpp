#include "OrdinaryEnemies.h"

OrdinaryEnemies::OrdinaryEnemies(float x, float y, int height, int weight, std::string name)
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
  breakerTexture.loadFromFile("../files/images/enemy.png");
  anim = AnimationManager(breakerTexture);
  anim.Create("move", 0, 0, 16, 16, 2, 0.002, 18);
  anim.Create("dead", 58, 0, 16, 16, 1, 0);
  anim.Set("move");
}

void OrdinaryEnemies::setDelivery() {
  SetHpGmg(DELIVERY_HP, DELIVERY_DMG);
  sf::Texture deliveryTexture;
  deliveryTexture.loadFromFile("../files/images/enemy.png");
  anim = AnimationManager(deliveryTexture);
  anim.Create("move", 0, 0, 16, 16, 2, 0.002, 18);
  anim.Create("dead", 58, 0, 16, 16, 1, 0);
  anim.Set("move");
}

void OrdinaryEnemies::setVirus() {
  SetHpGmg(VIRUS_HP, VIRUS_DMG);
  sf::Texture virusTexture;
  virusTexture.loadFromFile("../files/images/enemy.png");
  anim = AnimationManager(virusTexture);
  anim.Create("move", 0, 0, 16, 16, 2, 0.002, 18);
  anim.Create("dead", 58, 0, 16, 16, 1, 0);
  anim.Set("move");
}