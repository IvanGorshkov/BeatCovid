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
      antibodies.emplace_back(i.rect.left, i.rect.top, 32, 32, "antigen");
    }

    if (i.name == "vaccine") {
      vaccine.emplace_back(i.rect.left, i.rect.top, 32, 32, "vaccine");
    }
  }
}

// Обновление всех классов
void GameManager::Update(float time) {
  player->Update(time, obj);
  updateBullet(time);
  updateEnemy(time);
  updateAntibodies(time);
  updateVaccine(time);
  bulletPlayer();
  checkHitPlayer();
  checkHitEnemy();
}

// Вывод всех классов на экран
void GameManager::Draw(sf::RenderWindow &window) {
  player->DrawObjs(window);
  drawBullet(window);
  drawEnemy(window);
  drawAntibodies(window);
  drawVaccine(window);
  lables.DrawPoints(window, player->GetPoints());
  lables.DrawHp(window, player->GetHp());
  lables.DrawArm(window, player->GetArm());
}

Player *GameManager::GetPlayer() {
  return player;
}

// Огонь игроком
void GameManager::Fire() {

  if (player->GetPoints() > 0) {
    if (player->GetDir()) {
      playerBullets.emplace_back(player->GetRect().left - 20, player->GetRect().top + 10, -0.2, 0, player->GetDmg());
    } else {
      playerBullets.emplace_back(player->GetRect().left + player->GetRect().width + 10,
                                 player->GetRect().top + 10,
                                 0.2,
                                 0,
                                 player->GetDmg());
    }
    player->AddPoints(-1);
  }
}
// Методы для работы с Антителами

// Методы работы с классом Bullet
// Обновление Bullet
void GameManager::updateBullet(float time) {
  for (enemyBulletsIt = enemyBullets.begin(); enemyBulletsIt != enemyBullets.end(); enemyBulletsIt++) {
    if (enemyBulletsIt->IsDie()) {
      enemyBulletsIt = enemyBullets.erase(enemyBulletsIt);
    } else {
      enemyBulletsIt->Update(time, obj);
    }
  }

  for (playerBulletsIt = playerBullets.begin(); playerBulletsIt != playerBullets.end(); playerBulletsIt++) {
    if (playerBulletsIt->IsDie()) {
      playerBulletsIt = playerBullets.erase(playerBulletsIt);
    } else {
      playerBulletsIt->Update(time, obj);
    }
  }
}

// Вывод Bullet на экран
void GameManager::drawBullet(sf::RenderWindow &window) {
  for (enemyBulletsIt = enemyBullets.begin(); enemyBulletsIt != enemyBullets.end(); enemyBulletsIt++) {
    enemyBulletsIt->Draw(window);
  }

  for (playerBulletsIt = playerBullets.begin(); playerBulletsIt != playerBullets.end(); playerBulletsIt++) {
    playerBulletsIt->Draw(window);
  }
}

// Проверка на попадание во врага
void GameManager::checkHitEnemy() {
  for (playerBulletsIt = playerBullets.begin(); playerBulletsIt != playerBullets.end(); playerBulletsIt++) {
    for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
      if (playerBulletsIt->GetRect().intersects(enemiesIt->GetRect()) && playerBulletsIt->IsLife()) {
        enemiesIt->TakeDmg(playerBulletsIt->GetDmg());
        break;
      }
    }
  }
}

// Проверка на попадание в героя
void GameManager::checkHitPlayer() {
  for (enemyBulletsIt = enemyBullets.begin(); enemyBulletsIt != enemyBullets.end(); enemyBulletsIt++) {
    if (enemyBulletsIt->GetRect().intersects(player->GetRect()) && enemyBulletsIt->IsLife()) {
      player->TakeDamge(enemyBulletsIt->GetDmg());
      break;
    }
  }
}

// Начало стрельбы в героя
void GameManager::bulletPlayer() {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
    if (enemiesIt->GetTimer() > 1000) {
      float speed = 0.2;
      float X = (player->GetRect().left - enemiesIt->GetRect().left) / 16;
      float Y = (player->GetRect().top - enemiesIt->GetRect().top) / 16;

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

      // Пытаюсь научить дебилов не стрелять сквозь стену, пока не удачно
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

      if (X > 0) {
        enemyBullets.emplace_back(enemiesIt->GetRect().left + 20,
                                  enemiesIt->GetRect().top,
                                  dx,
                                  dy,
                                  enemiesIt->GetDmg());
      } else {
        enemyBullets.emplace_back(enemiesIt->GetRect().left - 16,
                                  enemiesIt->GetRect().top,
                                  dx,
                                  dy,
                                  enemiesIt->GetDmg());
      }

      enemiesIt->ResetTimer();
    }
  }
}

// Методы для работы с Enemy
// Обновление Enemy
void GameManager::updateEnemy(float time) {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
    if (enemiesIt->IsDie()) {
      enemiesIt = enemies.erase(enemiesIt);
    } else {
      enemiesIt->Update(time, obj);
    }
  }
}

// Вывод Enemy на экран
void GameManager::drawEnemy(sf::RenderWindow &window) {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
    enemiesIt->Draw(window);
  }
}

// Методы для работы с Antibodies
// Обновление Antibodies
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

// Вывод Antibodies на экран
void GameManager::drawAntibodies(sf::RenderWindow &window) {
  for (antibodiesIt = antibodies.begin(); antibodiesIt != antibodies.end(); antibodiesIt++) {
    antibodiesIt->Draw(window);
  }
}

// Методы для работы с Vaccine
// Обновление Vaccine
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

// Вывод Vaccine на экран
void GameManager::drawVaccine(sf::RenderWindow &window) {
  for (vaccineIt = vaccine.begin(); vaccineIt != vaccine.end(); vaccineIt++) {
    vaccineIt->Draw(window);
  }
}
