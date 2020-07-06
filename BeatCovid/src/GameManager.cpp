#include "GameManager.h"
#include "cmath"
#include "Interface.h"

GameManager::GameManager(Level &lvl,
                         MusicManager &music,
                         const std::vector<int> &arms,
                         int points,
                         const std::vector<int> &stat,
                         const std::vector<float> &config)
    : obj(lvl.GetAllObjects()),
      music(music),
      stat(std::move(stat)),
      antigenPoints(config[1]),
      player(std::make_shared<Player>(lvl.GetObject("player"), arms, config[0], points)) {

  for (auto &i : obj) {
    if (i.name == "breaker" || i.name == "delivery" || i.name == "virus") {
      enemies.push_back(std::make_shared<OrdinaryEnemies>(i.rect.left, i.rect.top, 40, 64, i.name, config));
      i.rect.width = 40;
      i.rect.height = 64;
    }

    if (i.name == "police") {
      enemies.push_back(std::make_shared<Police>(i.rect.left, i.rect.top, 40, 64, config[2], config[3], config[4]));
      i.rect.width = 40;
      i.rect.height = 64;
    }

    if (i.name == "antigen" || i.name == "vaccine") {
      antibodies.emplace_back(i.rect.left, i.rect.top, 32, 32, i.name);
    }

    if (i.name == "auto") {
      safeTransports.emplace_back(i.rect.left, i.rect.top - 10, 200, 100, i.name, config);
    }

    if (i.name == "monorail") {
      safeTransports.emplace_back(i.rect.left, i.rect.top + 40, 976, 140, i.name, config);
    }

    if (i.name == "bus") {
      unSafeTransports.emplace_back(i.rect.left, i.rect.top - 10, 393, 100, i.name, config);
    }

    if (i.name == "metro") {
      unSafeTransports.emplace_back(i.rect.left, i.rect.top - 15, 924, 140, i.name, config);
    }

    if (i.name == "finish") {
      sick = std::make_shared<Sick>(i.rect.left - 15, i.rect.top - 32, 0, 0, 128, 64);
    }
  }

  music.PlayBackgroundGameMusic();
}

// Обновление всех классов
void GameManager::Update(float time) {
  player->Update(time, obj);

  if ((player->PlayFinishMusic() == 1 || player->PlayFinishMusic() == 2) && !player->GetAlive()) {
    music.PlayTreatPatientSound();
  }

  if (player->PlayFinishMusic() == 0) {
    music.StopTreatPatientSound();
  }

  bulletPlayer();
  updateBullet(time);
  updateEnemy(time);
  updateAntibodies();
  updateTransport(time);
  checkHitPlayer();
  checkHitEnemy();
  if (player->GetAlive()) {
    sick->SetAlive();
  }
  sick->Update(time, obj);
}

// Вывод всех классов на экран
void GameManager::Draw(sf::RenderWindow &window) {
  drawBullet(window);
  drawEnemy(window);
  drawAntibodies(window);
  drawTransport(window);
  lables.DrawPlayerData(window, player->GetPoints(), player->GetHp(), player->GetArm(), player->GetVaccine());
  if (player->IsFinishPosition()) {
    lables.DrawNoVaccine(window);
  }

  if (!player->IsDrive()) {
    player->DrawObjs(window);
  }
  sick->Draw(window);

  if (sick->GetEnd()) {
    player->SetFinish();
  }
}

std::shared_ptr<Player> GameManager::GetPlayer() {
  return player;
}

// Огонь игроком
void GameManager::Fire() {
  music.PlayHitPlayerSound();

  if (player->GetPoints() > 0) {
    player->SetKey("SPACE", true);
    if (player->GetDir()) {
      playerBullets.emplace_back(player->GetRect().left - 25,
                                 player->GetRect().top + 40,
                                 -BULLET_DX,
                                 0,
                                 player->GetDmg(),
                                 true);
    } else {
      playerBullets.emplace_back(player->GetRect().left + player->GetRect().width + 10,
                                 player->GetRect().top + 40,
                                 BULLET_DX,
                                 0,
                                 player->GetDmg(),
                                 true);
    }

    player->AddPoints(-1);
  }
}

// Садится в транспорт
void GameManager::TakeTransport() {
  for (safeTransportsIt = safeTransports.begin(); safeTransportsIt != safeTransports.end(); ++safeTransportsIt) {
    if (safeTransportsIt->GetRect().intersects(player->GetRect())) {
      if (safeTransportsIt->IsDrive()) {
        if (safeTransportsIt->GetName() == "auto") {
          stat[8]++;
        }

        if (safeTransportsIt->GetName() == "monorail") {
          stat[9]++;
        }
      }

      safeTransportsIt->SetDrive();
      player->SetDrive();
      if (safeTransportsIt->GetName() == "auto") {
        music.PlayCarSound();
      } else {
        music.PlayMetroSound();
      }
      break;
    }
  }

  for (unSafeTransportsIt = unSafeTransports.begin(); unSafeTransportsIt != unSafeTransports.end();
       ++unSafeTransportsIt) {
    if (unSafeTransportsIt->GetRect().intersects(player->GetRect())) {
      if (unSafeTransportsIt->IsDrive()) {
        if (unSafeTransportsIt->GetName() == "bus") {
          stat[10]++;
        }

        if (unSafeTransportsIt->GetName() == "metro") {
          stat[11]++;
        }
      }

      unSafeTransportsIt->SetDrive();
      player->SetDrive();
      if (unSafeTransportsIt->GetName() == "bus") {
        music.PlayCarSound();
      } else {
        music.PlayMetroSound();
      }
      break;
    }
  }
}

std::vector<int> GameManager::GetStat() {
  return stat;
}

// Методы работы с классом Bullet
// Обновление Bullet
void GameManager::updateBullet(float time) {
  for (enemyBulletsIt = enemyBullets.begin(); enemyBulletsIt != enemyBullets.end(); ++enemyBulletsIt) {
    if (enemyBulletsIt->IsDie()) {
      enemyBulletsIt = enemyBullets.erase(enemyBulletsIt);
    } else {
      enemyBulletsIt->Update(time, obj);
    }
  }

  for (playerBulletsIt = playerBullets.begin(); playerBulletsIt != playerBullets.end(); ++playerBulletsIt) {
    if (playerBulletsIt->IsDie()) {
      playerBulletsIt = playerBullets.erase(playerBulletsIt);
    } else {
      playerBulletsIt->Update(time, obj);
    }
  }
}

// Вывод Bullet на экран
void GameManager::drawBullet(sf::RenderWindow &window) {
  for (enemyBulletsIt = enemyBullets.begin(); enemyBulletsIt != enemyBullets.end(); ++enemyBulletsIt) {
    enemyBulletsIt->Draw(window);
  }

  for (playerBulletsIt = playerBullets.begin(); playerBulletsIt != playerBullets.end(); ++playerBulletsIt) {
    playerBulletsIt->Draw(window);
  }
}

// Проверка на попадание во врага
void GameManager::checkHitEnemy() {
  for (playerBulletsIt = playerBullets.begin(); playerBulletsIt != playerBullets.end(); ++playerBulletsIt) {
    for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); ++enemiesIt) {
      if (playerBulletsIt->GetRect().intersects((*enemiesIt)->GetRect()) && playerBulletsIt->IsLife()) {
        (*enemiesIt)->TakeDmg(playerBulletsIt->GetDmg());
        break;
      }
    }
  }
}

// Проверка на попадание в героя
void GameManager::checkHitPlayer() {
  for (enemyBulletsIt = enemyBullets.begin(); enemyBulletsIt != enemyBullets.end(); ++enemyBulletsIt) {
    if (enemyBulletsIt->GetRect().intersects(player->GetRect()) && enemyBulletsIt->IsLife()) {
      player->TakeDamge(enemyBulletsIt->GetDmg());
      break;
    }
  }
}

// Начало стрельбы в героя
void GameManager::bulletPlayer() {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); ++enemiesIt) {
    if ((*enemiesIt)->GetTimer() > ENEMY_HIT_TIME && (*enemiesIt)->IsLife()) {
      float X = (player->GetRect().left - (*enemiesIt)->GetRect().left) / 16;
      float Y = (player->GetRect().top - (*enemiesIt)->GetRect().top) / 16;
      // Дальность полета пули
      (*enemiesIt)->SetFire(true);
      if (std::abs(X) > 30 || std::abs(Y) > 30) {
        (*enemiesIt)->SetFire(false);
        (*enemiesIt)->ResetTimer();
        continue;
      }

      float dx, dy;
      if (Y / X > 1 || Y / X < -1) {
        dy = Y > 0 ? BULLET_DX : -BULLET_DX;
        dx = dy * X / Y;
      } else {
        dx = X > 0 ? BULLET_DX : -BULLET_DX;
        dy = dx * Y / X;
      }

      if (X > 0) {
        (*enemiesIt)->SetDir(false);
        enemyBullets.emplace_back((*enemiesIt)->GetRect().left + 70,
                                  (*enemiesIt)->GetRect().top + 10,
                                  dx,
                                  dy,
                                  (*enemiesIt)->GetDmg(),
                                  false);
      } else {
        (*enemiesIt)->SetDir(true);
        enemyBullets.emplace_back((*enemiesIt)->GetRect().left - 30,
                                  (*enemiesIt)->GetRect().top + 10,
                                  dx,
                                  dy,
                                  (*enemiesIt)->GetDmg(),
                                  false);
      }
      (*enemiesIt)->ResetTimer();

      music.PlayHitEnemySound();
    }
  }
}

// Методы для работы с Enemy
// Обновление Enemy
void GameManager::updateEnemy(float time) {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); ++enemiesIt) {
    if (auto police = std::dynamic_pointer_cast<Police>(*enemiesIt)) {
      if (!police->ISMetUser() && police->GetRect().intersects(player->GetRect())) {
        int penalty = police->Penatly();
        player->PenaltyPoints(penalty);

        if (penalty != 0) {
          stat[12]++;
        }

        if (penalty == 0) {
          stat[13]++;
        }
      }
    }

    (*enemiesIt)->Update(time, obj);

    if ((*enemiesIt)->GetDieSound()) {
      if ((*enemiesIt)->GetName() == "police") {
        stat[4]++;
      }

      if ((*enemiesIt)->GetName() == "breaker") {
        stat[5]++;
      }

      if ((*enemiesIt)->GetName() == "delivery") {
        stat[6]++;
      }

      if ((*enemiesIt)->GetName() == "virus") {
        stat[7]++;
      }

      music.PlayDiedEnemySound();
      (*enemiesIt)->SetDieSound();
    }
  }
}

// Вывод Enemy на экран
void GameManager::drawEnemy(sf::RenderWindow &window) {
  for (enemiesIt = enemies.begin(); enemiesIt != enemies.end(); ++enemiesIt) {
    if (auto police = std::dynamic_pointer_cast<Police>(*enemiesIt)) {
      if (police->IsDrawPenaltyMenu()) {
        Interface &interface = Interface::GetInstance(window);
        interface.PenaltyPolice(window);
      }

      if (police->ISDrawDiedMenu()) {
        Interface &interface = Interface::GetInstance(window);
        interface.DiedPolice(window);
        player->GoToStart();
      }
    }

    (*enemiesIt)->Draw(window);
  }
}

// Методы для работы с Antibodies
// Обновление Antibodies
void GameManager::updateAntibodies() {
  for (antibodiesIt = antibodies.begin(); antibodiesIt != antibodies.end(); ++antibodiesIt) {
    if (!antibodiesIt->IsLife()) {
      if (antibodiesIt->GetName() == "antigen") {
        stat[3]++;
        player->AddPoints(antigenPoints);
        music.PlayGetAntibodiesSound();
      }

      if (antibodiesIt->GetName() == "vaccine") {
        stat[2]++;
        player->SetVaccine(true);
        music.PlayGetVaccineSound();
      }

      antibodiesIt = antibodies.erase(antibodiesIt);
      break;
    } else {
      antibodiesIt->Update(player);
    }
  }
}

// Вывод Antibodies на экран
void GameManager::drawAntibodies(sf::RenderWindow &window) {
  for (antibodiesIt = antibodies.begin(); antibodiesIt != antibodies.end(); ++antibodiesIt) {
    antibodiesIt->Draw(window);
  }
}

// Методы для работы с Transport
// Обновление Transport
void GameManager::updateTransport(float time) {
  updateSafeTransport(time);
  updateUnSafeTransport(time);
}

void GameManager::updateSafeTransport(float time) {
  for (safeTransportsIt = safeTransports.begin(); safeTransportsIt != safeTransports.end(); ++safeTransportsIt) {
    safeTransportsIt->Update(time, obj);
    if (safeTransportsIt->IsDrive()) {
      if (!safeTransportsIt->GetDir()) {
        player->SetPosition(safeTransportsIt->GetRect().left + safeTransportsIt->GetRect().width - 100,
                            safeTransportsIt->GetRect().top + 32);
      } else {
        player->SetPosition(safeTransportsIt->GetRect().left + 30, safeTransportsIt->GetRect().top + 32);
      }
      break;
    }
  }
}

void GameManager::updateUnSafeTransport(float time) {
  for (unSafeTransportsIt = unSafeTransports.begin(); unSafeTransportsIt != unSafeTransports.end();
       ++unSafeTransportsIt) {
    unSafeTransportsIt->Update(time, obj);
    if (unSafeTransportsIt->IsDrive()) {
      if (!unSafeTransportsIt->GetDir()) {
        player->SetPosition(unSafeTransportsIt->GetRect().left + unSafeTransportsIt->GetRect().width - 100,
                            unSafeTransportsIt->GetRect().top + 32);
      } else {
        player->SetPosition(unSafeTransportsIt->GetRect().left + 30, unSafeTransportsIt->GetRect().top + 32);
      }
      player->TakeDamge(unSafeTransportsIt->GetDmg());
      break;
    }
  }
}

// Вывод Transport на экран
void GameManager::drawTransport(sf::RenderWindow &window) {
  drawSafeTransport(window);
  drawUnSafeTransport(window);
}

void GameManager::drawSafeTransport(sf::RenderWindow &window) {
  for (safeTransportsIt = safeTransports.begin(); safeTransportsIt != safeTransports.end(); ++safeTransportsIt) {
    safeTransportsIt->Draw(window);

    if (safeTransportsIt->GetRect().intersects(player->GetRect())) {
      lables.DrawTransportHelp(window, player->GetRect().left, player->GetRect().top);
    }

    if (safeTransportsIt->IsDrive()) {
      lables.DrawSafeTransportFuel(window, safeTransportsIt->GetFuel());
    }
  }
}

void GameManager::drawUnSafeTransport(sf::RenderWindow &window) {
  for (unSafeTransportsIt = unSafeTransports.begin(); unSafeTransportsIt != unSafeTransports.end();
       ++unSafeTransportsIt) {
    unSafeTransportsIt->Draw(window);

    if (unSafeTransportsIt->GetRect().intersects(player->GetRect())) {
      lables.DrawTransportHelp(window, player->GetRect().left, player->GetRect().top);
    }

    if (unSafeTransportsIt->IsDrive()) {
      lables.DrawUnSafeTransportDmg(window, unSafeTransportsIt->PrintDmg());
    }
  }
}
