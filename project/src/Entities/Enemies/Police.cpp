#include "Police.h"

Police::Police(float x, float y, int height, int weight, int hp, int dmg, int penalty)
    : Enemy(x, y, height, weight, hp, dmg, "police"),
      penalty(penalty),
      isMetUser(false),
      drawPenaltyMenu(false),
      drawDiedMenu(false) {

  sf::Texture policeTexture;
  policeTexture.loadFromFile(FILES_PATH"files/images/policemen.png");
  anim = AnimationManager(policeTexture);
  anim.Create("move", 4, 4, 64, 64, 3, 0.002, 72);
  anim.Create("fire", 4, 147, 64, 64, 3, 0.004, 72);
  anim.Create("dead", 4, 363, 64, 64, 3, 0.002, 72);
  anim.Set("move");
}

int Police::Penatly() {
  isMetUser = true;
  auto rand = std::rand() % 4;

  if (rand != 0) {
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