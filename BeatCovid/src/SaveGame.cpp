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

void Save::SavePoints(int points) {
  std::ofstream save_file(resourcePath() + "files/saves/save_points.txt");
  // points
  save_file << points;
  save_file.close();
}

int Save::GetPonits() {
  std::fstream save;
  save.open(resourcePath() + "files/saves/save_points.txt");
  if (!save.is_open()) {
    return 0;
  }

  char buff[50];
  int points;
  save.getline(buff, 50);
  points = atoi(buff);
  return points;
}

void Save::Load(GameManager &game) {
  std::ifstream save_file(resourcePath() + "files/saves/save.txt");
  char buff[50];
  save_file.getline(buff, 50);
  this->lvl = atoi(buff);
  save_file.getline(buff, 50);
  game.GetPlayer()->ChangeARM(atoi(buff));
  game.GetPlayer()->AddPoints(GetPonits());
}

std::vector<int> Save::GetArmors() {
  std::fstream save;
  save.open(resourcePath() + "files/saves/save_armor.txt");
  if (!save.is_open()) {
    std::vector<int> empty = {0, 0, 0};
    return empty;
  }

  char buff[50];
  std::vector<int> arms = {0, 0, 0};
  save.getline(buff, 50);
  arms[0] = atoi(buff);
  save.getline(buff, 50);
  arms[1] = atoi(buff);
  save.getline(buff, 50);
  arms[2] = atoi(buff);
  return arms;
}

void Save::SaveArmor(std::vector<int> vec) {
  std::ofstream save_armor_file(resourcePath() + "files/saves/save_armor.txt");
  save_armor_file << vec[0];
  save_armor_file << std::endl;
  save_armor_file << vec[1];
  save_armor_file << std::endl;
  save_armor_file << vec[2];
  save_armor_file << std::endl;

  save_armor_file.close();
}

std::vector<int> Save::LoadStat() {
  std::fstream saveStatFile(resourcePath() + "files/saves/save_stat.txt");
  std::vector<int> stat = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  if (!saveStatFile.is_open()) {
    return stat;
  } else {

    char buff[1000];
    for (int i = 0; i < 13; i++) {
      saveStatFile.getline(buff, 1000);
      stat[i] = atoi(buff);
    }

    saveStatFile.close();
    return stat;
  }
}

void Save::SaveStat(const std::vector<int> &stat) {
  std::ofstream saveStatFile(resourcePath() + "files/saves/save_stat.txt");

  for (int i = 0; i < 13; i++) {
    saveStatFile << stat[i];
    saveStatFile << std::endl;
  }

  saveStatFile.close();
}
