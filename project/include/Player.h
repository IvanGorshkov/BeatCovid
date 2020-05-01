#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Level_map.h"
#include "Entity.h"

class Player : public Entity {
 public:
  Player() = default;
  explicit Player(const Object& position);
  bool GetDir() const;
  void KeyCheck();
  float GetHp() const;
  float GetArm() const;
  float TakeDamge(float dmg);
  int GetDmg() const;
  void Update(float time, std::vector<Object> &obj) override;
  void Collision(int num, std::vector<Object> objs);
  void SetKey(std::string name, bool value);
  void AddPoints(int getPoints);
  int GetPoints() const;
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
