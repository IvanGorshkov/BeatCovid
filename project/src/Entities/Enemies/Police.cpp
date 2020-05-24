#include "Police.h"

Police::Police(float x, float y, int height, int weight)
    : Enemy(x, y, height, weight, POLICE_HP, POLICE_DMG),
      penalty(POLICE_PENALTY),
      isMetUser(false),
      drawPenaltyMenu(false),
      drawDiedMenu(false) {
  sf::Texture policeTexture;
  policeTexture.loadFromFile("../files/images/policemen.png");
  anim = AnimationManager(policeTexture);
  anim.Create("move", 4, 4, 64, 64, 3, 0.002, 72);
  anim.Create("fire", 4, 147, 64, 64, 3, 0.004, 72);
  anim.Create("dead", 58, 0, 16, 16, 1, 0);
  anim.Set("move");
}

int Police::Penatly() {
  isMetUser = true;
  auto rand = std::rand() % 2;

  if (rand == 1) {
    rand = penalty;
    drawPenaltyMenu = true;

  } else {
    rand = 0;
    drawDiedMenu = true;
  }

  return rand;
}

bool Police::IsDrawPenaltyMenu() {
  if (drawPenaltyMenu) {
    drawPenaltyMenu = false;
    return true;
  }

  return false;
}

bool Police::ISDrawDiedMenu() {
  if (drawDiedMenu) {
    drawDiedMenu = false;
    return true;
  }

  return false;
}

bool Police::ISMetUser() const {
  return isMetUser;
}