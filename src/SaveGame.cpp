#include "SaveGame.h"
#include <fstream>
#include <sstream>

Save::Save()
:lvl(1),
points(0),
armors(3, 0),
stat(14, 0),
config(15, 0) {
    loadInt(lvl, LVL_FILE);
    loadInt(points, POINTS_FILE);
    loadVector(armors, ARMOR_FILE);
    loadVector(stat, STAT_FILE);
    loadVector(config, CONFIG_DEFAULT_FILE);
    
    checkLvl();
}

Save::~Save() {
    saveInt(lvl, LVL_FILE);
    saveInt(points, POINTS_FILE);
    saveVector(armors, ARMOR_FILE);
    saveVector(stat, STAT_FILE);
}

void Save::NextLvl() {
    lvl += 1;
}

void Save::LastLvl() {
    lvl -= 1;
}

void Save::SetEndGame() {
    lvl = 0;
}

int Save::GetLvl() const {
    return lvl;
}

std::string Save::GetLvlName() {
    return (MAPS_PATH + std::to_string(lvl) + ".tmx");
}

int Save::GetPoints() const {
    return points;
}

std::vector<int> Save::GetArmors() const {
    return armors;
}

std::vector<int> Save::GetStat() const {
    return stat;
}

std::vector<int> Save::GetConfig() const {
    return config;
}

void Save::SetPoints(int points) {
    this->points = points;
}

void Save::SetArmors(const std::vector<int> &armors) {
    this->armors = armors;
}

void Save::SetStat(const std::vector<int> &stat) {
    this->stat = stat;
}

void Save::RemoveSaves() {
    lvl = 1;
    points = 0;
    
    for (int &i : armors) {
        i = 0;
    }
    
    checkLvl();
}

bool Save::CheckEndGame() const {
    std::ifstream nextMap(MAPS_PATH + std::to_string(lvl + 1) + ".tmx");
    bool exist = nextMap.is_open();
    nextMap.close();
    return !exist;
}

void Save::checkLvl() {
    if (stat[0] != 0 && lvl == 1) {
        NextLvl();
    }
}

void Save::loadVector(std::vector<int> &vec, const std::string &path) {
    std::ifstream saveFile(path);
    
    if (saveFile.is_open()) {
        for (int &i : vec) {
            saveFile >> i;
        }
    }
    
    saveFile.close();
}

void Save::loadInt(int &i, const std::string &path) {
    std::ifstream saveFile(path);
    
    if (saveFile.is_open()) {
        saveFile >> i;
    }
    
    saveFile.close();
}

void Save::saveVector(const std::vector<int> &vec, const std::string &path) {
    std::ofstream saveFile(path);
    
    for (int i : vec) {
        saveFile << i << std::endl;
    }
    
    saveFile.close();
}

void Save::saveInt(const int &i, const std::string &path) {
    std::ofstream saveFile(path);
    saveFile << i;
    saveFile.close();
}
