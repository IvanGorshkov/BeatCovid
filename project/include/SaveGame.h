#pragma once

#include "GameManager.h"

#define MAX_LVL 2
#define LVL_FILE FILES_PATH"files/saves/save_lvl.txt"
#define MAPS_PATH FILES_PATH"files/maps/"
#define POINTS_FILE FILES_PATH"files/saves/save_points.txt"
#define ARMOR_FILE FILES_PATH"files/saves/save_armor.txt"
#define STAT_FILE FILES_PATH"files/saves/save_stat.txt"
#define CONFIG_FILE FILES_PATH"files/saves/save_config.txt"
#define CONFIG_DEFAULT_FILE FILES_PATH"files/saves/save_config_default.txt"

class Save {
 public:
  Save();
  void ChangeLvl();
  void GoToStart();
  int GetLvl() const;

  std::string GetLvlName();

  static bool IsExistLvlFile();
  static bool IsExistPointsFile();
  static bool IsExistArmorFile();
  static bool IsExistStatFile();
  static bool IsExistConfigFile();
  static bool IsExistConfigDefaultFile();

  static void RemoveGameSaves();
  static void RemoveConfig();

  void LoadGame(GameManager &game);
  void SaveGame(GameManager &game) const;

  static int LoadLvl();
  static void SaveLvl(int lvl);
  static int LoadPoints();
  static void SavePoints(int points);
  static std::vector<int> LoadArmors();
  static void SaveArmor(const std::vector<int> &vec);
  static std::vector<int> LoadStat();
  static void SaveStat(const std::vector<int> &stat);
  static std::vector<float> LoadConfig();
  static void SaveConfig(const std::vector<float> &stat);

 private:
  int lvl;
};
