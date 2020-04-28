#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Player.h"
#include "../include/Bullet.h"

#define BLOKSIZE 16

class Enemy {
public:
    explicit Enemy(int x, int y, sf::Color color);
    void draw(sf::RenderWindow &windows);
    void update(float offsetX, float offsetY);
    void Hit(Player& player, BulletManager& bullet) const;

    sf::FloatRect rect;
private:
    int dmg;
    int countDmg;
    bool isLife;
    float currentFrame;
    sf::Sprite sprite;
};

class Police: public Enemy {
public:
    Police(int x, int y);
};

class Delivery: public Enemy {
public:
    Delivery(int x, int y);
};

class Breaker: public Enemy {
public:
    Breaker(int x, int y);
};

class Virus: public Enemy {
public:
    Virus(int x, int y);
};
