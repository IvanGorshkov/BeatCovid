#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include "GameManager.h"
#include "SaveGame.h"
#include "MusicManager.h"

class Interface {
 public:
  Interface() = default;
  static void MainMenu(sf::RenderWindow &window, Save &save);
  static bool NewGameWarningMenu(sf::RenderWindow &window, MusicManager &menuMusic, Save &save);
  static bool Shop(sf::RenderWindow &window, Save &save);
  static bool GameMenu(sf::RenderWindow &window, GameManager &game, MusicManager &menuMusic);
  static void Buy(std::vector<int> arm_vector, int index);
  static void StartNewGame(sf::RenderWindow &window, Save &save, MusicManager &menuMusic);
  static bool DiedMenu(sf::RenderWindow &window);
  static bool WinMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic);
  static bool PenaltyPolice(sf::RenderWindow &window);
  static bool DiedPolice(sf::RenderWindow &window);
  static bool AboutMenu(sf::RenderWindow &window, MusicManager &menuMusic);
};
