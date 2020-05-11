#pragma once

#include "Entity.h"
#include "Player.h"
#include <string>

class Antibodies : public Entity {
 public:
  Antibodies(float x, float y, float w, float h, std::string name);
  void Update(Player *player);
  void Update(float time, std::vector<Object> &obj) override;
};
