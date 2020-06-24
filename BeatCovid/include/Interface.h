#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include "GameManager.h"
#include "SaveGame.h"
#include "MusicManager.h"

class Interface {
 public:
  Interface() = default;
  static void StartNewGame(sf::RenderWindow &window, Save &save, MusicManager &menuMusic);
  static bool GameMenu(sf::RenderWindow &window, GameManager &game, MusicManager &menuMusic);
  static void MainMenu(sf::RenderWindow &window, Save &save);
  static bool DiedMenu(sf::RenderWindow &window);
  static bool PenaltyPolice(sf::RenderWindow &window);
  static bool DiedPolice(sf::RenderWindow &window);
  static bool WinMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic);
  static bool Shop(sf::RenderWindow &window, Save &save);
  static void Buy(std::vector<int> arm_vector, int index);
};
