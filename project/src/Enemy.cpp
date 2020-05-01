#include "Enemy.h"

Enemy::Enemy(float x, float y,int height, int weight)
    : Entity(x, y, 0, 0, height, weight) {
  sf::Texture enemyTexture;
  enemyTexture.loadFromFile("../enemy.png");
  anim = AnimationManager(enemyTexture);
  anim.create("move", 0, 0, 16, 16, 2, 0.002, 18);
  anim.create("dead", 58, 0, 16, 16, 1, 0);
  anim.set("move");
}

void Enemy::Update(float time, std::vector<Object> &obj) {
  anim.set("move");
  timer += time;
  anim.tick(time);
}

float Enemy::GetTimer() const {
  return timer;
}

void Enemy::ResetTimer() {
  timer = 0;
}

void Enemy::setDie() {
  isLife = false;
}
//
//Police::Police(int x, int y)
//    : Enemy(x, y, sf::Color::Black) {
//}
//
//Delivery::Delivery(int x, int y)
//    : Enemy(x, y, sf::Color::Yellow) {
//}
//
//Breaker::Breaker(int x, int y)
//    : Enemy(x, y, sf::Color::Red) {
//}
//
//Virus::Virus(int x, int y)
//    : Enemy(x, y, sf::Color::Green) {
//}