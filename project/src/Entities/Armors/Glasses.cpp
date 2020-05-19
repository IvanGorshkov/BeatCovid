#include "Glasses.h"

Glasses::Glasses(float x, float y, float w, float h, int lvl) : Armor(x, y, w, h, lvl) {
  sf::Texture player_t;
  switch (lvl) {
    case 0:
      player_t.loadFromFile("../files/images/free.png");
      arm = 0;
      break;
    case 1:
      player_t.loadFromFile("../files/images/glasses.png");
      arm = 1;
      break;
    case 2:
      player_t.loadFromFile("../files/images/glasses.png");
      arm = 2;
      break;
    case 3:
      player_t.loadFromFile("../files/images/glasses.png");
      arm = 3;
      break;
    case 4:
      player_t.loadFromFile("../files/images/glasses.png");
      arm = 4;
      break;
  }

  anim = AnimationManager(player_t);
  anim.Create("walk", 0, 244, 40, 50, 6, 0.005, 40);
  anim.Create("stay", 0, 187, 42, 52, 3, 0.002, 42);
  anim.Create("die", 0, 1199, 59, 41, 7, 0.004, 59);
  anim.Create("jump", 0, 528, 29, 30, 4, 0.0045, 38);
  anim.Create("win", 0, 744, 33, 76, 4, 0.0045, 38);
  anim.Create("lay", 0, 436, 80, 20, 1, 0);
  anim.Set("stay");
}