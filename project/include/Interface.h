#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Interface {
 public:
  Interface() = default;
  void StartNewGame(sf::RenderWindow &window);
  bool GameMenu(sf::RenderWindow &window);
  void MainMenu(sf::RenderWindow &window);
  bool DiedMenu(sf::RenderWindow &window);
  bool WinMenu(sf::RenderWindow &window);
};
