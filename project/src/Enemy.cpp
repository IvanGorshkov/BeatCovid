#include "../include/Enemy.h"

Enemy::Enemy(int x, int y, sf::Color color)
    : currentFrame(0)
    , isLife(true) {
    sf::Texture tileSet;
    tileSet.loadFromFile("/Users/ivangorshkov/beatcovid/tileset.png");
    sprite.setTexture(tileSet);
    rect = sf::FloatRect(x * BLOKSIZE, y * BLOKSIZE,BLOKSIZE,BLOKSIZE);
    sprite.setColor(color);
}

void Enemy::Hit(Player& player, BulletManager& bullet) const {
    float X = (player.rect.left - this->rect.left) / BLOKSIZE;
    float Y = (player.rect.top - this->rect.top) / BLOKSIZE;
    float dx = X > 0 ? 0.2 : -0.2;
    float dy = dx * Y/X;
    bullet.add(this->rect.left, this->rect.top, dx, dy);
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