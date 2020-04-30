#include "GameManager.h"

GameManager::GameManager(Level &lvl) {
  obj = lvl.GetAllObjects();
  player = new Player(lvl.GetObject("player"));
}

// Функция обновляет все наши классы (Игрок, враг, антитела, вакцина)
void GameManager::Update(float time) {
  player->status(time, obj);
  bullets.update(time);
}

void GameManager::draw(sf::RenderWindow &window) {
  player->draw(window);
  bullets.draw(window);
}

Player *GameManager::GetPlayer() {
  return player;
}
void GameManager::Fire() {
  bullets.add(player->getRect().left + player->getRect().width, player->getRect().top + 10, 0.2, 0);
}
