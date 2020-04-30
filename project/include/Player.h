//
// Created by Ivan Gorshkov on 25.04.2020.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Level_map.h"

class Player {
 public:
  Player() = default;
  explicit Player(Object position);
  void draw(sf::RenderWindow &window);
  bool GetDir();
  void keyCheck();
  float getHp();
  float getArm();
  float takeDamge(float dmg);
  void status(float time, std::vector<Object> objs);
  sf::FloatRect getRect();
  void collision(int num, std::vector<Object> objs);
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
