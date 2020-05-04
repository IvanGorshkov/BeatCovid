#pragma once

#include "Enemy.h"

class EnemyManager {
    EnemyManager(Level& lvl);
private:
    std::list<Enemy> enemies;
    std::list<Enemy>::iterator it;
};