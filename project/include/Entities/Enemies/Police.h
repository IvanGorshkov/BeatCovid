#pragma once

#include "Enemy.h"

#define POLICE_HP 3
#define POLICE_DMG 6
#define POLICE_PENALTY 50

class Police : public Enemy {
 public:
  explicit Police(float x, float y, int height, int weight, int hp, int dmg, int penalty);
  int Penatly();
  bool IsDrawPenaltyMenu();
  bool ISDrawDiedMenu();
  bool ISMetUser() const;

 private:
  int penalty;
  bool drawPenaltyMenu;
  bool drawDiedMenu;
  bool isMetUser;
};

