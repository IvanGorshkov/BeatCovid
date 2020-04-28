//
// Created by Ivan Gorshkov on 25.04.2020.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Level_map.h"

class Player {
 public:
  std::vector<Object> obj;
  explicit Player(AnimationManager &a_m, Level &lev);
  void draw(sf::RenderWindow &window);
  void keyCheck();
  float getHp();
  float getArm();
  float takeDamge(float dmg);
  void status(float time);
  sf::FloatRect getRect();
  void collision (int num);
  void setKey(std::string name, bool value);

 private:
  enum {
    STAY,
    RUN,
    JUMP,
    LAY,
  } STATE;

  AnimationManager anim;
  std::map<std::string, bool> key;
  bool dir;
  float hp;
  float arm;
  float max_jump;
  int points;
  bool isGround;
  float dx;
  float dy;
  sf::FloatRect rect;
};
