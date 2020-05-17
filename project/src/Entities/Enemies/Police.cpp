#include "Police.h"

Police::Police(float x, float y, int height, int weight)
    : Enemy(x, y, height, weight, 3, 6), penalty(50)
    , isMetUser(false)
    , drawPenaltyMenu(false)
    , drawDiedMenu(false) {
  sf::Texture policeTexture;
  policeTexture.loadFromFile("../files/images/enemy.png");
  anim = AnimationManager(policeTexture);
  anim.Create("move", 0, 0, 16, 16, 2, 0.002, 18);
  anim.Create("dead", 58, 0, 16, 16, 1, 0);
  anim.Set("move");
}

void Police::Update(float time, std::vector<Object> &obj) {
  timerHit += time;

  if (hp < 0) {
    dx = 0;
    dy = 0;
    anim.Set("dead");
    isLife = false;
  }

  anim.Tick(time);
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