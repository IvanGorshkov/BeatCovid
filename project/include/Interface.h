#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "GameManager.h"
#include "SaveGame.h"
#include <string>

class Interface {
 public:
  Interface() = default;
  static void StartNewGame(sf::RenderWindow &window, Save &save);
  static bool GameMenu(sf::RenderWindow &window, GameManager &game);
  static void MainMenu(sf::RenderWindow &window, Save &save);
  static bool DiedMenu(sf::RenderWindow &window);
  static bool PenaltyPolice(sf::RenderWindow &window);
  static bool DiedPolice(sf::RenderWindow &window);
  static bool WinMenu(sf::RenderWindow &window, Save &save, GameManager &game);
  static bool Shop(sf::RenderWindow &window, Save &save);
  static void Buy(std::vector<int> arm_vector, int index);
};
