#include <fstream>
#include "SaveGame.h"
#include "ResourcePath.hpp"

Save::Save() {
  this->lvl = 1;
}

void Save::ChangeLvl() {
  this->lvl += 1;
}

int Save::GetLvl() const {
  return this->lvl;
}

std::string Save::GetLvlName() {
  std::ifstream save_file(resourcePath() + "files/saves/save.txt");
  std::ifstream save_stat(resourcePath() + "files/saves/save_stat.txt");

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
  std::string lvlname = resourcePath() + "files/maps/";
  return (lvlname += std::to_string(GetLvl()) + ".tmx");
}

void Save::GoToStart() {
  this->lvl = 1;
}

bool Save::SaveExists() {
  std::fstream save;
  save.open(resourcePath() + "files/saves/save.txt");
  return save.is_open();
}

bool Save::SaveExistsP() {
  std::fstream save;
  save.open(resourcePath() + "files/saves/save_points.txt");
  return save.is_open();
}

bool Save::SaveExistsA() {
  std::fstream save;
  save.open(resourcePath() + "files/saves/save_armor.txt");
  return save.is_open();
}

void Save::Load(GameManager &game) {
  std::ifstream save_file(resourcePath() + "files/saves/save.txt");
  char buff[50];
  save_file.getline(buff, 50);
  this->lvl = atoi(buff);
  save_file.getline(buff, 50);
  game.GetPlayer()->ChangeARM(atoi(buff));
  game.GetPlayer()->AddPoints(LoadPoints());
}

void Save::SaveGame(GameManager &game) const {
  std::ofstream save_file(resourcePath() + "files/saves/save.txt");
  // lvl
  save_file << this->lvl;
  save_file << std::endl;
  // arm
  save_file << game.GetPlayer()->GetArm();
  save_file << std::endl;
  save_file.close();
  SavePoints(game.GetPlayer()->GetPoints());
}

std::vector<int> Save::LoadArmors() {
  std::fstream saveArmorsFile(resourcePath() + "files/saves/save_armor.txt");
  std::vector<int> armors;
  armors.resize(3, 0);

  if (!saveArmorsFile.is_open()) {
    return armors;
  }

  char buff[50];
  for (int i = 0; i < armors.size(); i++) {
    saveArmorsFile.getline(buff, 50);
    armors[i] = atoi(buff);
  }

  saveArmorsFile.close();
  return armors;
}

void Save::SaveArmor(std::vector<int> armors) {
  std::ofstream saveArmorsFile(resourcePath() + "files/saves/save_armor.txt");

  for (int i = 0; i < armors.size(); i++) {
    saveArmorsFile << armors[i];
    saveArmorsFile << std::endl;
  }

  saveArmorsFile.close();
}

int Save::LoadPoints() {
  std::fstream save(resourcePath() + "files/saves/save_points.txt");
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
  std::ofstream save_file(resourcePath() + "files/saves/save_points.txt");
  save_file << points;
  save_file.close();
}

std::vector<int> Save::LoadStat() {
  std::fstream saveStatFile(resourcePath() + "files/saves/save_stat.txt");
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
  std::ofstream saveStatFile(resourcePath() + "files/saves/save_stat.txt");

  for (int i : stat) {
    saveStatFile << i;
    saveStatFile << std::endl;
  }

  saveStatFile.close();
}

std::vector<float> Save::LoadConfig() {
  std::fstream saveConfigFile(resourcePath() + "files/saves/save_config.txt");
  std::vector<float> config;
  config.resize(20, 0);

  if (!saveConfigFile.is_open()) {
    return config;
  } else {

    char buff[100];
    for (float &i : config) {
      saveConfigFile.getline(buff, 100);
      i = atoi(buff);
    }

    saveConfigFile.close();
    return config;
  }
}

void Save::SaveConfig(const std::vector<float> &config) {
  std::fstream saveConfigFile(resourcePath() + "files/saves/save_config.txt");

  for (float i : config) {
    saveConfigFile << i;
    saveConfigFile << std::endl;
  }

  saveConfigFile.close();
}
