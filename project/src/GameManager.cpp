#include "GameManager.h"

GameManager::GameManager(Level &lvl) {
  obj = lvl.GetAllObjects();
  player = new Player(lvl.GetObject("player"));
}

// Общие методы Менеджера
void GameManager::Update(float time) {
  player->status(time, obj);

  for (it = entities.begin(); it != entities.end(); it++) {
    if (!(*it)->IsLife()) {
      it = entities.erase(it);
    } else {
      (*it)->Update(time, obj);
    }
  }
}

void GameManager::Draw(sf::RenderWindow &window) {
  player->draw(window);

  for (it = entities.begin(); it != entities.end(); it++) {
    (*it)->Draw(window);
  }
}

Player *GameManager::GetPlayer() {
  return player;
}
void GameManager::Fire() {
  if (player->GetDir()) {
    addBullet(player->getRect().left, player->getRect().top + 10, -0.2, 0);
  } else {
    addBullet(player->getRect().left + player->getRect().width, player->getRect().top + 10, 0.2, 0);
  }

}

// Методы для работы с Bullet
void GameManager::addBullet(float x, float y, float dx, float dy) {
  entities.push_back(new Bullet(x, y, dx, dy));
}
