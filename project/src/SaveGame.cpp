#include "SaveGame.h"
#include <fstream>
#include <sstream>

Save::Save() {
  this->lvl = 1;
}

void Save::ChangeLvl() {
  this->lvl += 1;
}

int Save::GetLvl() const {
  return this->lvl;
}

void Save::SetEndGame() {
  this->lvl = 0;
}

std::string Save::GetLvlName() {
  lvl = LoadLvl();

  std::ifstream save_stat(STAT_FILE);

  if (save_stat.is_open()) {
    char buff[50];
    save_stat.getline(buff, 50);

    if (atoi(buff) != 0 && lvl == 1) {
      ChangeLvl();
    }
  }

  std::string lvlname = MAPS_PATH;
  return (lvlname += std::to_string(lvl) + ".tmx");
}

void Save::SaveGame(int points) const {
  SaveLvl(lvl);
  SavePoints(points);
}

bool Save::IsExistLvlFile() {
  std::fstream save(LVL_FILE);
  return save.is_open();
}

void Save::RemoveGameSaves() {
  std::fstream saveLvl(LVL_FILE);
  if (saveLvl.is_open()) {
    std::ostringstream ssLvl;
    ssLvl << LVL_FILE;
    remove(ssLvl.str().c_str());
  }
  saveLvl.close();

  std::fstream saveArmor(ARMOR_FILE);
  if (saveArmor.is_open()) {
    std::ostringstream ssArmor;
    ssArmor << ARMOR_FILE;
    remove(ssArmor.str().c_str());
  }
  saveArmor.close();

  std::fstream savePoints(POINTS_FILE);
  if (savePoints.is_open()) {
    std::ostringstream ssPoints;
    ssPoints << POINTS_FILE;
    remove(ssPoints.str().c_str());
  }
  savePoints.close();
}

void Save::RemoveConfig() {
  std::fstream saveConfig(CONFIG_FILE);
  if (saveConfig.is_open()) {
    std::ostringstream ssConfig;
    ssConfig << CONFIG_FILE;
    remove(ssConfig.str().c_str());
  }
  saveConfig.close();
}

int Save::LoadLvl() {
  std::ifstream save(LVL_FILE);
  if (!save.is_open()) {
    return 1;
  }

  char buff[50];
  int level;
  save.getline(buff, 50);
  level = atoi(buff);
  return level;
}

void Save::SaveLvl(int lvl) {
  std::ofstream save_file(LVL_FILE);
  save_file << lvl;
  save_file.close();
}

int Save::LoadPoints() {
  std::ifstream save(POINTS_FILE);
  if (!save.is_open()) {
    return 0;
  }

  char buff[50];
  int points;
  save.getline(buff, 50);
  points = atoi(buff);
  return points;
}

void Save::SavePoints(int points) {
  std::ofstream save_file(POINTS_FILE);
  save_file << points;
  save_file.close();
}

std::vector<int> Save::LoadArmors() {
  std::ifstream saveArmorsFile(ARMOR_FILE);
  std::vector<int> armors;
  armors.resize(3, 0);

  if (!saveArmorsFile.is_open()) {
    return armors;
  }

  char buff[50];
  for (int &armor : armors) {
    saveArmorsFile.getline(buff, 50);
    armor = atoi(buff);
  }

  saveArmorsFile.close();
  return armors;
}

void Save::SaveArmor(const std::vector<int> &arm) {
  std::ofstream saveArmorsFile(ARMOR_FILE);

  for (int armor : arm) {
    saveArmorsFile << armor;
    saveArmorsFile << std::endl;
  }

  saveArmorsFile.close();
}

std::vector<int> Save::LoadStat() {
  std::ifstream saveStatFile(STAT_FILE);
  std::vector<int> stat;
  stat.resize(14, 0);

  if (!saveStatFile.is_open()) {
    return stat;
  } else {
    char buff[1000];
    for (int &i : stat) {
      saveStatFile.getline(buff, 1000);
      i = atoi(buff);
    }

    saveStatFile.close();
    return stat;
  }
}

void Save::SaveStat(const std::vector<int> &stat) {
  std::ofstream saveStatFile(STAT_FILE);

  for (int i : stat) {
    saveStatFile << i;
    saveStatFile << std::endl;
  }

  saveStatFile.close();
}

std::vector<float> Save::LoadConfig() {
  std::ifstream saveConfigFile;
  std::vector<float> config;
  config.resize(20, 0);

  std::fstream saveConfig(CONFIG_FILE);
  if (saveConfig.is_open()) {
    saveConfigFile.open(CONFIG_FILE);
  } else {
    saveConfigFile.open(CONFIG_DEFAULT_FILE);
  }
  saveConfig.close();

  char buff[100];
  for (float &i : config) {
    saveConfigFile.getline(buff, 100);
    i = atoi(buff);
  }

  saveConfigFile.close();
  return config;
}

void Save::SaveConfig(const std::vector<float> &config) {
  std::ofstream saveConfigFile(CONFIG_FILE);

  for (float i : config) {
    saveConfigFile << i;
    saveConfigFile << std::endl;
  }

  saveConfigFile.close();
}


