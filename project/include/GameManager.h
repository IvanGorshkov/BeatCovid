#pragma once

#include "Level_map.h"
#include "Entity.h"
#include <list>

class GameManager {
public:
    explicit GameManager(Level& lvl);
    void Update(float time);
private:
    std::vector<Object> obj;
    std::list<Entity> entities;
    std::list<Entity>::iterator it;
};