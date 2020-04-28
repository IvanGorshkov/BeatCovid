//
// Created by Ivan Gorshkov on 25.04.2020.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationMenager.h"

class Player {
 public:
  explicit Player(AnimationMenager &a_m);
  void draw(sf::RenderWindow &window, float offsetX, float offsetY);
  void keyCheck();
  float getHp();
  float getArm();
  float takeDamge(float dmg);
  void status(float time, std::string *TileMap);
  sf::FloatRect getRect();
  void collision (int num, std::string *TileMap);
  void setKey(std::string name, bool value);

 private:
  enum {
    STAY,
    RUN,
    JUMP,
    LAY,
  } STATE;

  AnimationMenager anim;
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
