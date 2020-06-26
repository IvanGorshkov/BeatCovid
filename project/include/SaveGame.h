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

  void GoToStart();

  static bool SaveExistsP();
  static bool SaveExistsA();


  static std::vector<int> LoadArmors();
  static void SaveArmor(std::vector<int> vec);
  static int LoadPoints();
  static void SavePoints(int points);
  static std::vector<int> LoadStat();
  static void SaveStat(const std::vector<int> &stat);
  static std::vector<float> LoadConfig();
  static void SaveConfig(const std::vector<float> &stat);

 private:
  int lvl;
};
