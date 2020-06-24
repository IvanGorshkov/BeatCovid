#include "Interface.h"
#include "SaveGame.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 800), "Beat COVID-19", sf::Style::Titlebar);
  window.setFramerateLimit(120);
  Save save;
  Interface::MainMenu(window, save);
  return 0;
}
