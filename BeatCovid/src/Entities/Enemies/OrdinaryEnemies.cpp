#include "OrdinaryEnemies.h"
#include "ResourcePath.hpp"
#include <utility>

OrdinaryEnemies::OrdinaryEnemies(float x, float y, int height, int weight, const std::string &name, std::vector<float> config)
    : Enemy(x, y, height, weight, name),
    config(std::move(config)) {

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
  SetHpGmg(config[5], config[6]);
  sf::Texture breakerTexture;
  breakerTexture.loadFromFile(resourcePath() + "files/images/breaker.png");
  anim = AnimationManager(breakerTexture);
  anim.Create("move", 4, 4, 64, 64, 6, 0.002, 72);
  anim.Create("fire", 68, 72, 64, 64, 2, 0.004, 72);
  anim.Create("dead", 4, 148, 64, 64, 3, 0.002, 72);
  anim.Set("move");
}

void OrdinaryEnemies::setDelivery() {
  SetHpGmg(config[7], config[8]);
  sf::Texture deliveryTexture;
  deliveryTexture.loadFromFile(resourcePath() + "files/images/delivery.png");
  anim = AnimationManager(deliveryTexture);
  anim.Create("move", 4, 4, 64, 64, 4, 0.002, 72);
  anim.Create("fire", 4, 72, 64, 64, 4, 0.004, 72);
  anim.Create("dead", 4, 148, 64, 64, 3, 0.002, 72);
  anim.Set("move");
}

void OrdinaryEnemies::setVirus() {
  SetHpGmg(config[9], config[10]);
  sf::Texture virusTexture;
  virusTexture.loadFromFile(resourcePath() + "files/images/virus.png");
  anim = AnimationManager(virusTexture);
  anim.Create("move", 4, 4, 64, 64, 4, 0.002, 72);
  anim.Create("fire", 4, 72, 64, 64, 3, 0.004, 72);
  anim.Create("dead", 4, 148, 64, 64, 2, 0.002, 72);
  anim.Set("move");
}
