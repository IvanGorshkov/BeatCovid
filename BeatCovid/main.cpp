#include "Interface.h"
#include "SaveGame.h"

int main() {
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Beat COVID-19", sf::Style::Fullscreen);
//  sf::RenderWindow window(sf::VideoMode(1280, 800), "Beat COVID-19");
  window.setFramerateLimit(120);
  window.setVerticalSyncEnabled(true);
  Interface& interface = Interface::GetInstance(window);
  interface.MainMenu(window);
  return 0;
} 
