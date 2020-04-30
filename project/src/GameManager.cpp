#include "GameManager.h"

GameManager::GameManager(Level &lvl) {
  obj = lvl.GetAllObjects();
  player = new Player(lvl.GetObject("player"));
  for (auto &i : obj) {
    if (i.name == "police" || i.name == "delivery" || i.name == "breaker" || i.name == "virus") {
      enemies.emplace_back(i.rect.left, i.rect.top, i.rect.width, i.rect.height);
    }
  }
}

// Общие методы Менеджера
void GameManager::Update(float time) {
  player->status(time, obj);

  updateBullet(time);
  updateEnemy(time);
//  hitPlayer();
}

void GameManager::Draw(sf::RenderWindow &window) {
  player->draw(window);

  drawBullet(window);
  drawEnemy(window);
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
  bullets.emplace_back(x, y, dx, dy);
}

void GameManager::updateBullet(float time) {
  for (bulletsIt = bullets.begin(); bulletsIt != bullets.end(); bulletsIt++) {
    if (!bulletsIt->IsLife()) {
      bulletsIt = bullets.erase(bulletsIt);
    } else {
      bulletsIt->Update(time, obj);
    }
  }
}

void GameManager::drawBullet(sf::RenderWindow &window) {
  for (bulletsIt = bullets.begin(); bulletsIt != bullets.end(); bulletsIt++) {
    bulletsIt->Draw(window);
  }
}

// Методы для работы с Enemy
void GameManager::updateEnemy(float time) {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
    if (!enemiesIt->IsLife()) {
      enemiesIt = enemies.erase(enemiesIt);
    } else {
      enemiesIt->Update(time, obj);
    }
  }
}

void GameManager::drawEnemy(sf::RenderWindow &window) {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
    enemiesIt->Draw(window);
  }
}

void GameManager::hitPlayer() {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
    float speed = 0.1;
    float X = (player->getRect().left - enemiesIt->GetRect().left) / 16;
    float Y = (player->getRect().top - enemiesIt->GetRect().top) / 16;
    float dx, dy;
    if (Y / X > 1 || Y / X < -1) {
      dy = Y > 0 ? speed : -speed;
      dx = dy * X / Y;
    } else {
      dx = X > 0 ? speed : -speed;
      dy = dx * Y / X;
    }

    addBullet(enemiesIt->GetRect().left, enemiesIt->GetRect().top, dx, dy);
  }
}