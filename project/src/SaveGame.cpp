#include "SaveGame.h"

#include <fstream>

void Save::SaveGame(GameManager &game) {
    std::ofstream fout("../files/saves/save1.txt");
    fout << "HP: " << game.GetPlayer()->GetHp();
    fout << std::endl;
    fout << "ARMOR: " << game.GetPlayer()->GetArm();
    fout << std::endl;
    fout << "VACCINE: " << game.GetPlayer()->GetVaccine();
    fout << std::endl;
    fout << "POINTS: " << game.GetPlayer()->GetPoints();
    fout.close();
}
