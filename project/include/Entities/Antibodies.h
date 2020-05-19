#pragma once

#include "Entity.h"
#include "Player.h"
#include <string>
#define ANTIGEN_POINTS 100

class Antibodies : public Entity {
 public:
  Antibodies(float x, float y, float w, float h, const std::string &name);
  void Update(Player *player);
  void Update(float time, std::vector<Object> &obj) override;
  std::string GetName();
 private:
  std::string name;
  void setAntigen();
  void setVaccine();
};
