#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include <list>

#define BLOKSIZE 16

class Bullet {
public:
    Bullet(float x, float y, float dx, float dy);
    void update(float time, AnimationManager& anim);
    void draw(sf::RenderWindow &window, AnimationManager& anim);

private:
    float dx;
    float dy;
    bool isLife;
    //AnimationMenager anim;
    sf::FloatRect rect;
    sf::Sprite sprite;
};