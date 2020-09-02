#pragma once

#include <vector>
#include <string>
#include "ResourcePath.hpp"

#define MAPS_PATH resourcePath() + "files/maps/"
#define LVL_FILE resourcePath() + "files/saves/save_lvl.txt"
#define POINTS_FILE resourcePath() + "files/saves/save_points.txt"
#define ARMOR_FILE resourcePath() + "files/saves/save_armor.txt"
#define STAT_FILE resourcePath() + "files/saves/save_stat.txt"
#define CONFIG_FILE resourcePath() + "files/saves/save_config.txt"
#define CONFIG_DEFAULT_FILE resourcePath() + "files/saves/save_config_default.txt"

class Save {
public:
    Save();
    ~Save();
    void NextLvl();
    void LastLvl();
    void SetEndGame();
    int GetLvl() const;
    int GetPoints() const;
    std::vector<int> GetArmors() const;
    std::vector<int> GetStat() const;
    std::vector<int> GetConfig() const;
    
    void SetPoints(int points);
    void SetArmors(const std::vector<int> &armors);
    void SetStat(const std::vector<int> &stat);
    
    std::string GetLvlName();
    
    void RemoveSaves();
    
    bool CheckEndGame() const;
    
private:
    void checkLvl();
    
    void loadVector(std::vector<int> &vec, const std::string &path);
    void loadInt(int &i, const std::string &path);
    void saveVector(const std::vector<int> &vec, const std::string &path);
    void saveInt(const int &i, const std::string &path);
    
    int lvl;
    int points;
    std::vector<int> armors;
    std::vector<int> stat;
    std::vector<int> config;
};
