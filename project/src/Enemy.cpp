#include "Enemy.h"

Enemy::Enemy(int x, int y, sf::Color color)
    : currentFrame(0), isLife(true) {
  sf::Texture tileSet;
  tileSet.loadFromFile("../tileset.png");
  sprite.setTexture(tileSet);
  rect = sf::FloatRect(x * BLOKSIZE, y * BLOKSIZE, BLOKSIZE, BLOKSIZE);
  sprite.setColor(color);
}

void Enemy::Hit(Player &player, BulletManager &bullet) const {
  float speed = 0.1;
  float X = (player.getRect().left - this->rect.left) / BLOKSIZE;
  float Y = (player.getRect().top - this->rect.top) / BLOKSIZE;
  float dx, dy;
  if (Y / X > 1 || Y / X < -1) {
    dy = Y > 0 ? speed : -speed;
    dx = dy * X / Y;
  } else {
    dx = X > 0 ? speed : -speed;
    dy = dx * Y / X;
  }
  //bullet.add(this->rect.left, this->rect.top, dx, dy);
}

void Enemy::draw(sf::RenderWindow &windows) {
  windows.draw(sprite);
}

void Enemy::update(float offsetX, float offsetY) {
  sprite.setTextureRect(sf::IntRect(0, 0, BLOKSIZE, BLOKSIZE));
  sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
}

Police::Police(int x, int y)
    : Enemy(x, y, sf::Color::Black) {
}

Delivery::Delivery(int x, int y)
    : Enemy(x, y, sf::Color::Yellow) {
}

Breaker::Breaker(int x, int y)
    : Enemy(x, y, sf::Color::Red) {
}

Virus::Virus(int x, int y)
    : Enemy(x, y, sf::Color::Green) {
}