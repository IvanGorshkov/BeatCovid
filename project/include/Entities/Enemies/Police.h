#pragma once

#include "Enemy.h"

class Police : public Enemy {
 public:
  explicit Police(float x, float y, int height, int weight);
  void Update(float time, std::vector<Object> &obj) override;
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

