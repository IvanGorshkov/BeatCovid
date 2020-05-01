//
// Created by Ivan Gorshkov on 25.04.2020.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Level_map.h"
#include "Entity.h"

class Player: public Entity {
 public:
  Player() = default;
  explicit Player(Object position);
  void draw(sf::RenderWindow &window);
  bool GetDir();
  void keyCheck();
  float getHp();
  float getArm();
  float takeDamge(float dmg);
  int GetDmg();
  void Update(float time, std::vector<Object> &obj) override;
  sf::FloatRect getRect();
  void collision(int num, std::vector<Object> objs);
  void setKey(std::string name, bool value);
  void AddPoints(int points);
  int GetPoints();
  bool GetVaccine();
  void SetVaccine(bool value);

 private:
  enum {
    STAY,
    RUN,
    JUMP,
    LAY,
  } STATE;

  std::map<std::string, bool> key;
  bool dir;
  int dmg;
  float hp;
  float arm;
  float max_jump;
  int points;
  bool isGround;
  bool vaccine;
};
