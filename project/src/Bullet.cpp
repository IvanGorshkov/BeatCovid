#include "Bullet.h"

Bullet::Bullet(float x, float y, float dx, float dy)
        : dx(dx)
        , dy(dy)
        , isLife(true) {
//    sf::Texture bulletTexture;
//    bulletTexture.loadFromFile("/Users/alekhin/beatcovid/dark.png");
//    anim.create("move", bulletTexture, 7, 10, 8, 8, 1, 0);
//    anim.create("explode", bulletTexture, 27, 7, 18, 18, 4, 0.01, 29);
    rect = sf::FloatRect(x, y, 16, 16);
    //anim.set("move");
}

void Bullet::draw(sf::RenderWindow &window, AnimationManager& anim) {
    anim.set("move");
    anim.draw(window,rect.left, rect.top + rect.height);
}

void Bullet::update(float time, AnimationManager& anim) {
    rect.left += dx * time;
    rect.top += dy * time;

    anim.tick(time);
}