#include "Interface.h"
#include "SaveGame.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 800), "Beat COVID-19");
  window.setFramerateLimit(120);
  Save save;
  Interface::MainMenu(window, save);
  remove("../files/saves/save.txt");
  return 0;
}
