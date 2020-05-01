#include "GameManager.h"
#include "cmath"

GameManager::GameManager(Level &lvl) {
  obj = lvl.GetAllObjects();
  player = new Player(lvl.GetObject("player"));
  for (auto &i : obj) {
    if (i.name == "police" || i.name == "delivery" || i.name == "breaker" || i.name == "virus") {
      enemies.emplace_back(i.rect.left, i.rect.top, i.rect.width, i.rect.height);
    }
    if (i.name == "antigen") {
      antibodies.emplace_back(i.rect.left, i.rect.top, 32, 32);
    }

    if (i.name == "vaccine") {
      vaccine.emplace_back(i.rect.left, i.rect.top, 32, 32);
    }
  }
}

// Общие методы Менеджера
void GameManager::Update(float time) {
  player->Update(time, obj);
  updateBullet(time);
  updateEnemy(time);
  hitPlayer();
  diePlayer();
  dieEnemy();
  updateAntibodies(time);
  updateVaccine(time);
}

void GameManager::Draw(sf::RenderWindow &window) {
  drawAntibodies(window);
  drawVaccine(window);
  drawBullet(window);
  drawEnemy(window);
  player->Draw(window);
  lables.DrawPoints(window,player->GetPoints());
}

Player *GameManager::GetPlayer() {
  return player;
}
void GameManager::Fire() {
  if (player->GetPoints() > 0) {
    if (player->GetDir()) {
      playerBullets.emplace_back(player->getRect().left, player->getRect().top + 10, -0.2, 0);
    } else {
      playerBullets.emplace_back(player->getRect().left + player->getRect().width, player->getRect().top + 10, 0.2, 0);
    }
    player->AddPoints(-1);
  }
}
// Методы для работы с Антителами

void GameManager::drawAntibodies(sf::RenderWindow &window) {
  for (antibodiesIt = antibodies.begin(); antibodiesIt != antibodies.end(); antibodiesIt++) {
    antibodiesIt->Draw(window);
  }
}

void GameManager::updateAntibodies(float time) {
  for (antibodiesIt = antibodies.begin(); antibodiesIt != antibodies.end(); antibodiesIt++) {
    if (!antibodiesIt->IsLife()) {
      player->AddPoints(100);
      antibodiesIt = antibodies.erase(antibodiesIt);
      break;
    } else {
      antibodiesIt->Update(player);
    }
  }
}

// Методы для работы с Vaccine

void GameManager::drawVaccine(sf::RenderWindow &window) {
  for (vaccineIt = vaccine.begin(); vaccineIt != vaccine.end(); vaccineIt++) {
    vaccineIt->Draw(window);
  }
}

void GameManager::updateVaccine(float time) {
  for (vaccineIt = vaccine.begin(); vaccineIt != vaccine.end(); vaccineIt++) {
    if (!vaccineIt->IsLife()) {
      player->SetVaccine(true);
      vaccineIt = vaccine.erase(vaccineIt);
      break;
    } else {
      vaccineIt->Update(player);
    }
  }
}


// Методы для работы с Bullet

void GameManager::updateBullet(float time) {
  for (enemyBulletsIt = enemyBullets.begin(); enemyBulletsIt != enemyBullets.end(); enemyBulletsIt++) {
    if (!enemyBulletsIt->IsLife()) {
      enemyBulletsIt = enemyBullets.erase(enemyBulletsIt);
    } else {
      enemyBulletsIt->Update(time, obj);
    }
  }

  for (playerBulletsIt = playerBullets.begin(); playerBulletsIt != playerBullets.end(); playerBulletsIt++) {
    if (!playerBulletsIt->IsLife()) {
      playerBulletsIt = playerBullets.erase(playerBulletsIt);
    } else {
      playerBulletsIt->Update(time, obj);
    }
  }
}

void GameManager::drawBullet(sf::RenderWindow &window) {
  for (enemyBulletsIt = enemyBullets.begin(); enemyBulletsIt != enemyBullets.end(); enemyBulletsIt++) {
    enemyBulletsIt->Draw(window);
  }

  for (playerBulletsIt = playerBullets.begin(); playerBulletsIt != playerBullets.end(); playerBulletsIt++) {
    playerBulletsIt->Draw(window);
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

void GameManager::dieEnemy() {
  for (playerBulletsIt = playerBullets.begin(); playerBulletsIt != playerBullets.end(); playerBulletsIt++) {
    for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
      if (playerBulletsIt->GetRect().intersects(enemiesIt->GetRect())) {
        enemiesIt->setDie();
        break;
      }
    }
  }
}

void GameManager::diePlayer() {
  for (enemyBulletsIt = enemyBullets.begin(); enemyBulletsIt != enemyBullets.end(); enemyBulletsIt++) {
    if (enemyBulletsIt->GetRect().intersects(player->getRect())) {
      player->takeDamge(0.5);
      break;
    }
  }
}

void GameManager::hitPlayer() {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
    if (enemiesIt->GetTimer() > 1000) {
      float speed = 0.2;
      float X = (player->getRect().left - enemiesIt->GetRect().left) / 16;
      float Y = (player->getRect().top - enemiesIt->GetRect().top) / 16;

      // Дальность полета пули
      if (std::abs(X) > 30 || std::abs(Y) > 30) {
        enemiesIt->ResetTimer();
        break;
      }

      float dx, dy;
      if (Y / X > 1 || Y / X < -1) {
        dy = Y > 0 ? speed : -speed;
        dx = dy * X / Y;
      } else {
        dx = X > 0 ? speed : -speed;
        dy = dx * Y / X;
      }

      // Пытаюсь научить дебилов не стрелять сквозь стену
//      for (auto &i : obj) {
//        float currentX = enemiesIt->GetRect().left;
//
//        if ( enemiesIt->GetRect().top < player->getRect().top) {
//          for (float currentY = enemiesIt->GetRect().top; currentY < player->getRect().top; currentY += dy * 16) {
//            auto currentRect = sf::FloatRect(currentX, currentY, 25, 25);
//            if (currentRect.intersects(i.rect)) {
//              break;
//            }
//            currentX += dx * 16;
//          }
//        } else {
//          for (float currentY = enemiesIt->GetRect().top; currentY > player->getRect().top; currentY += dy * 16) {
//            auto currentRect = sf::FloatRect(currentX, currentY, 25, 25);
//            if (currentRect.intersects(i.rect)) {
//              break;
//            }
//            currentX += dx * 16;
//          }
//        }
//      }

      enemyBullets.emplace_back(enemiesIt->GetRect().left, enemiesIt->GetRect().top, dx, dy);
      enemiesIt->ResetTimer();
    }
  }
}