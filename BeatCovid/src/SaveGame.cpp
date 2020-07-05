#include <fstream>
#include <sstream>
#include "SaveGame.h"

Save::Save() {
  this->lvl = 1;
}

void Save::ChangeLvl() {
  this->lvl += 1;
}

int Save::GetLvl() const {
  return this->lvl;
}

void Save::GoToStart() {
  this->lvl = 1;
}

std::string Save::GetLvlName() {
  std::ifstream save_file(LVL_FILE);
  std::ifstream save_stat(STAT_FILE);

  if (save_file.is_open()) {
    char buff[50];
    save_file.getline(buff, 50);
    this->lvl = atoi(buff);
  } else {
    GoToStart();
    char buff[50];
    save_stat.getline(buff, 50);
    if (save_stat.is_open() && atoi(buff) != 0) {
      ChangeLvl();
    }
  }
  std::string lvlname = MAPS_PATH;
  return (lvlname += std::to_string(GetLvl()) + ".tmx");
}

void Save::LoadGame(GameManager &game) {
  lvl = LoadLvl();
  std::vector<int> armors = LoadArmors();
  int armor = 0;
  for (int i : armors) {
     armor += i;
  }
  game.GetPlayer()->ChangeARM(armor);
  game.GetPlayer()->AddPoints(LoadPoints());
}

void Save::SaveGame(GameManager &game) const {
  SaveLvl(lvl);
  SavePoints(game.GetPlayer()->GetPoints());
}

std::vector<int> Save::LoadArmors() {
  std::ifstream saveArmorsFile(ARMOR_FILE);
  std::vector<int> armors;
  armors.resize(3, 0);

  if (!saveArmorsFile.is_open()) {
    return armors;
  }

  char buff[50];
  for (int & armor : armors) {
    saveArmorsFile.getline(buff, 50);
    armor = atoi(buff);
  }

  saveArmorsFile.close();
  return armors;
}

void Save::SaveArmor(const std::vector<int>& armors) {
  std::ofstream saveArmorsFile(ARMOR_FILE);

  for (int armor : armors) {
    saveArmorsFile << armor;
    saveArmorsFile << std::endl;
  }

  saveArmorsFile.close();
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
    
  if (IsExistConfigFile()) {
      saveConfigFile.open(CONFIG_FILE);
  } else {
      saveConfigFile.open(CONFIG_DEFAULT_FILE);
  }
    
    char buff[100];
    for (float &i : config) {
      saveConfigFile.getline(buff, 100);
      i = atoi(buff);
    }

    saveConfigFile.close();
    return config;
}

void Save::RemoveConfig() {
    std::ostringstream ssConfig;
    ssConfig << resourcePath() << CONFIG_FILE;
    remove(ssConfig.str().c_str());
}

void Save::SaveConfig(const std::vector<float> &config) {
  std::ofstream saveConfigFile(CONFIG_FILE);

  for (float i : config) {
    saveConfigFile << i;
    saveConfigFile << std::endl;
  }

  saveConfigFile.close();
}

void Save::RemoveGameSaves() {
  if (IsExistLvlFile()) {
    std::ostringstream ssSaveLvl;
    ssSaveLvl << resourcePath() << LVL_FILE;
    remove(ssSaveLvl.str().c_str());
  }

  if (IsExistArmorFile()) {
    std::ostringstream ssSaveArmor;
    ssSaveArmor << resourcePath() << ARMOR_FILE;
    remove(ssSaveArmor.str().c_str());
  }

  if (IsExistPointsFile()) {
    std::ostringstream ssSavePoints;
    ssSavePoints << resourcePath() << POINTS_FILE;
    remove(ssSavePoints.str().c_str());
  }
}

bool Save::IsExistLvlFile() {
  std::fstream save(LVL_FILE);
  return save.is_open();
}

bool Save::IsExistPointsFile() {
  std::fstream save(POINTS_FILE);
  return save.is_open();
}

bool Save::IsExistArmorFile() {
  std::fstream save(ARMOR_FILE);
  return save.is_open();
}

bool Save::IsExistStatFile() {
  std::fstream save(STAT_FILE);
  return save.is_open();
}

bool Save::IsExistConfigFile() {
  std::fstream save(CONFIG_FILE);
  return save.is_open();
}

bool Save::IsExistConfigDefaultFile() {
  std::fstream save(CONFIG_DEFAULT_FILE);
  return save.is_open();
}

void Save::SaveLvl(int lvl) {
  std::ofstream save_file(LVL_FILE);
  save_file << lvl;
  save_file.close();
}

int Save::LoadLvl() {
  std::ifstream save(LVL_FILE);
  if (!save.is_open()) {
    return 0;
  }

  char buff[50];
  int level;
  save.getline(buff, 50);
  level = atoi(buff);
  return level;
}


