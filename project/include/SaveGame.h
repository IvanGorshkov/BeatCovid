#pragma once

#include "GameManager.h"

class Save {
 public:
  Save();
  void SaveGame(GameManager &game);
  void ChangeLvl();
  std::string GetLvlName();
  bool SaveExists();
  int GetLvl() const;
  void Load(GameManager &game);
  std::vector<int> GetArmors();
  void GoToStart();
  void SaveArmor(std::vector<int> vec);
  void SavePoints(int points);
  int GetPonits();
  bool SaveExistsP();
  bool SaveExistsA();
 private:
  int lvl;
};
