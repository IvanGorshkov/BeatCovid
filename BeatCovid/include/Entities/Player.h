#pragma once

#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Robe.h"
#include "Shoes.h"
#include "Cap.h"

class Player : public Entity {
 public:
  explicit Player(const Object &position, std::vector<int> armors, float hp, int dmg, int points);
  void Update(float time, std::vector<Object> &obj) override;
  void SetKey(const std::string &name, bool value);
  bool GetDir() const;
  float GetHp() const;
  float GetArm() const;
  float TakeDamge(float dmg);
  int GetDmg() const;
  void AddPoints(int getPoints);
  int GetPoints() const;
  void PenaltyPoints(int penaltyPoints);
  bool GetVaccine() const;
  void SetVaccine(bool value);
  void DrawObjs(sf::RenderWindow &window);
  void GoToStart();
  bool GetFinish() const;
  void SetPosition(float x, float y);
  std::vector<int> GetMainData();
  void SetDrive();
  bool IsDrive() const;
  bool IsFinishPosition() const;
  bool GetAlive() const;
  void SetFinish(bool getFinish = true);
  int PlayFinishMusic() const;

 private:
  void keyCheck();
  void collision(int num, std::vector<Object> &objs);
  void setAnim(const std::string &str);
  void setDir(bool dir);

  enum {
    STAY,
    RUN,
    JUMP,
    LAY,
    WALKLAY,
  } STATE;

  std::map<std::string, bool> key;
  Object startPlayerPosition;
  int dmgC;
  int fireC;
  int treatC;
  bool treat;
  bool finish;
  bool alive;
  bool dir;
  bool fire;
  int dmg;
  float hp;
  float arm;
  float max_jump;
  int points;
  bool isGround;
  bool tookDmg;
  bool vaccine;
  Robe bathrobe;
  Shoes shoes;
  Cap cap;
  int playFinishMusic;
  bool isDrive;
  bool isFinishPosition;
};
