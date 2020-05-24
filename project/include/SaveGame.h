#pragma once

#include "GameManager.h"

class Save {
 public:
  Save();
  void SaveGame(GameManager &game) const;
  void ChangeLvl();
  std::string GetLvlName();
  static bool SaveExists();
  int GetLvl() const;
  void Load(GameManager &game);
  static std::vector<int> GetArmors();
  void GoToStart();
  static void SaveArmor(std::vector<int> vec);
  static void SavePoints(int points);
  static int GetPonits();
  static bool SaveExistsP();
  static bool SaveExistsA();
 private:
  int lvl;
};