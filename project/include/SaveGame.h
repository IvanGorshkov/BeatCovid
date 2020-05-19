#pragma once

#include "GameManager.h"

class Save {
 public:
  int lvl;
  Save();
  void SaveGame(GameManager &game);
  void ChangeLvl();
  std::string GetLvlName();
  bool SaveExists();
  int GetLvl() const;
  void Load(GameManager &game);
  void GoToStart();
};
