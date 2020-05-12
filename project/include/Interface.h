#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Interface {
 public:
  Interface() = default;
  static void StartNewGame(sf::RenderWindow &window);
  static bool GameMenu(sf::RenderWindow &window);
  static void MainMenu(sf::RenderWindow &window);
  static bool DiedMenu(sf::RenderWindow &window);
  static bool PenaltyPolice(sf::RenderWindow &window);
  static bool DiedPolice(sf::RenderWindow &window);
  static bool WinMenu(sf::RenderWindow &window);
};
