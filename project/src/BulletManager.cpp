#include "BulletManager.h"

BulletManager::BulletManager() {
}

void BulletManager::update(float time) {
  for (it = bullets.begin(); it != bullets.end(); it++) {
    if (!it->IsLife()) {
      it = bullets.erase(it);
    } else {
      it->Update(time);
    }
  }
}

void BulletManager::draw(sf::RenderWindow &window) {
  for (it = bullets.begin(); it != bullets.end(); it++) {
    it->Draw(window);
  }
}

void BulletManager::add(float x, float y, float dx, float dy) {
  bullets.emplace_back(x, y, dx, dy);
}
