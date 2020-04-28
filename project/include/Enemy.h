#pragma once

#include <SFML/Graphics.hpp>
#include "Level_map.h"
#include "Player.h"
#include "BulletManager.h"

#define BLOKSIZE 16

class Enemy {
public:
    explicit Enemy(int x, int y, sf::Color color);
    void draw(sf::RenderWindow &windows);
    void update(float offsetX, float offsetY);
    void Hit(Player &player, BulletManager &bullet) const;

private:
    int dmg;
    int countDmg;
    bool isLife;
    float currentFrame;
    sf::FloatRect rect;
    sf::Sprite sprite;
};







class Police : public Enemy {
public:
    Police(int x, int y);
};

class Delivery : public Enemy {
public:
    Delivery(int x, int y);
};

class Breaker : public Enemy {
public:
    Breaker(int x, int y);
};

class Virus : public Enemy {
public:
    Virus(int x, int y);
};
