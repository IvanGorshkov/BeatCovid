#pragma once

#include <SFML/Graphics.hpp>
#include <list>

enum Direction {
    RIGHTDIRECTION,
    LEFTDIRECTION
};

#define BLOKSIZE 16

class Bullet {
public:
    Bullet(float x, float y, float dx, float dy);
    void update(float time, float offsetX, float offsetY);
    void draw(sf::RenderWindow& window);
private:
    float x;
    float y;
    float dx;
    float dy;
    bool isLife;
    sf::Sprite sprite;
};

class BulletManager {
public:
    void update(float time, float offsetX, float offsetY);
    void add(float x, float y, float dx, float dy);
    void draw(sf::RenderWindow& window);
private:
    std::list<Bullet> bullets;
    std::list<Bullet>::iterator it;
};

