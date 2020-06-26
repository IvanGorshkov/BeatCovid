#pragma once

#include "GameManager.h"

#define MAX_LVL 2

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
  static std::vector<int> LoadStat();
  static void SaveStat(const std::vector<int> &stat);

 private:
  int lvl;
};
