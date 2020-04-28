#include "../include/Bullet.h"

Bullet::Bullet(float x, float y, float dx, float dy)
    : x(x)
    , y(y)
    , dx(dx)
    , dy(dy)
    , isLife(true) {
    sf::Texture tileSet;
    tileSet.loadFromFile("/Users/ivangorshkov/beatcovid/tileset.png");
    sprite.setTexture(tileSet);
    sprite.setColor(sf::Color::Blue);
}

void Bullet::draw(sf::RenderWindow &window) {
    sprite.setTextureRect(sf::IntRect(0, 0, BLOKSIZE, BLOKSIZE));
    window.draw(sprite);
}

void Bullet::update(float time, float offsetX, float offsetY) {
    x += dx * time;
    y += dy * time;
    sprite.setPosition(x - offsetX, y - offsetY);
}

void BulletManager::update(float time, float offsetX, float offsetY) {
    for (it = bullets.begin(); it != bullets.end(); it++) {
        it->update(time, offsetX, offsetY);
    }
}

void BulletManager::draw(sf::RenderWindow &window) {
    for (it = bullets.begin(); it != bullets.end(); it++) {
        it->draw(window);
    }
}

void BulletManager::add(float x, float y, float dx, float dy) {
    bullets.emplace_back(x, y, dx, dy);
}