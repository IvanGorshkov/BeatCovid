#pragma once

#include "Bullet.h"
#include "Level_map.h"
#include "AnimationManager.h"

class BulletManager {
public:
    BulletManager();
    void update(float time, AnimationManager& anim);
    void add(float x, float y, float dx, float dy);
    void draw(sf::RenderWindow &window, AnimationManager& animb);

private:
    std::list<Bullet> bullets;
    std::list<Bullet>::iterator it;
};

