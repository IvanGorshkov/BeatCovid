#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Level_map.h"
#include "Entity.h"
#include "Robe.h"
#include "Gloves.h"
#include "Glasses.h"
#include "Mask.h"

class Player : public Entity {
 public:
  Player() = default;
  explicit Player(const Object &position);
  bool GetDir() const;
  void KeyCheck();
  float GetHp() const;
  float GetArm() const;
  float TakeDamge(float dmg);
  int GetDmg() const;
  void Update(float time, std::vector<Object> &obj) override;
  void Collision(int num, std::vector<Object> &objs);
  void SetKey(const std::string& name, bool value);
  void AddPoints(int getPoints);
  int GetPoints() const;
  void PenaltyPoints(int penaltyPoints);
  bool GetVaccine() const;
  void SetVaccine(bool value);
  void DrawObjs(sf::RenderWindow &window);
  AnimationManager GetAnim();
  void GoToStart(const Object &position);
  bool GetFinish() const;
  void ChangeHP(int hp);
  void ChangeARM(int arm);
 private:
  enum {
    STAY,
    RUN,
    JUMP,
    LAY,
  } STATE;

  std::map<std::string, bool> key;
  bool finish;
  bool dir;
  int dmg;
  float hp;
  float arm;
  float max_jump;
  int points;
  bool isGround;
  bool vaccine;
  Robe bathrobe;
  Gloves gloves;
  Glasses glasses;
  Mask mask;
};
