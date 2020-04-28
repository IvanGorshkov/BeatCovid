#include "BulletManager.h"

BulletManager::BulletManager() {

}

void BulletManager::update(float time, AnimationManager& anim) {
    for (it = bullets.begin(); it != bullets.end(); it++) {
        it->update(time, anim);
    }
}

void BulletManager::draw(sf::RenderWindow &window, AnimationManager& animb) {
    for (it = bullets.begin(); it != bullets.end(); it++) {
        it->draw(window, animb);
    }
}

void BulletManager::add(float x, float y, float dx, float dy) {
    bullets.emplace_back(x, y, dx, dy);
}
