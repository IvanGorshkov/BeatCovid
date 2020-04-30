#include "GameManager.h"

GameManager::GameManager(Level &lvl) {
    obj = lvl.GetAllObjects();
}

// Функция обновляет все наши классы (Игрок, враг, антитела, вакцина)
void GameManager::Update(float time) {

}