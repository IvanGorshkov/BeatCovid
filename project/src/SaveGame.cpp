#include "SaveGame.h"

#include <fstream>


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
    std::string lvlname = "../files/maps/";
    return (lvlname += std::to_string(GetLvl()) + ".tmx");
}

void Save::GoToStart() {
    this->lvl = 1;
}

bool Save::SaveExists() {
    std::fstream save;
    save.open("../files/saves/save.txt");
    if (save.is_open()) {
        return true;
    } else {
        return false;
    }
}

void Save::SaveGame(GameManager &game) {
  std::ofstream save_file("../files/saves/save.txt");
  save_file << this->lvl;
  save_file << std::endl;
  // hp
  save_file << game.GetPlayer()->GetHp();
  save_file << std::endl;
  // arm
  save_file << game.GetPlayer()->GetArm();
  save_file << std::endl;
  // points
  save_file << game.GetPlayer()->GetPoints();
  save_file.close();
}

void Save::Load(GameManager &game) {
    std::ifstream save_file("../files/saves/save.txt");
    char buff[50];
    save_file.getline(buff, 50);
    this->lvl = atoi(buff);
    save_file.getline(buff, 50);
    game.GetPlayer()->ChangeHP(atoi(buff));
    save_file.getline(buff, 50);
    game.GetPlayer()->ChangeARM(atoi(buff));
    save_file.getline(buff, 50);
    game.GetPlayer()->AddPoints(atoi(buff));
}
