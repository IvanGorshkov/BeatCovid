#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "GameManager.h"
#include <string>

class Interface {
 public:
  Interface() = default;
  void StartNewGame(sf::RenderWindow &window, std::string lvlName);
  bool GameMenu(sf::RenderWindow &window, GameManager &game);
  void MainMenu(sf::RenderWindow &window);
  bool DiedMenu(sf::RenderWindow &window);
  bool WinMenu(sf::RenderWindow &window);
};
