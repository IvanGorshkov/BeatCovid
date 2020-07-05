#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include "GameManager.h"
#include "SaveGame.h"
#include "MusicManager.h"
#include "InterfaceLabel.h"
#include "InterfaceSprite.h"
#include "InterfaceButton.h"
#include "InterfaceTable.h"
#include "InterfaceMultiLineLabel.h"

#define BACK_BUTTON_SHIFT 30

class Interface {
 public:
  explicit Interface(sf::RenderWindow &window);
  void MainMenu(sf::RenderWindow &window, Save &save);

  static bool PenaltyPolice(sf::RenderWindow &window);
  static bool DiedPolice(sf::RenderWindow &window);

 private:
  bool gameMenu(sf::RenderWindow &window, GameManager &game, MusicManager &menuMusic);
  bool shopMenu(sf::RenderWindow &window, Save &save);
  bool newGameWarningMenu(sf::RenderWindow &window, MusicManager &menuMusic, Save &save);
  void buy(std::vector<int> arm_vector, int index);
  void startNewGame(sf::RenderWindow &window, Save &save, MusicManager &menuMusic);

  bool winMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic);
  bool nextLvlMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic);
  bool aboutMenu(sf::RenderWindow &window, MusicManager &menuMusic);

  void diedMenu(sf::RenderWindow &window, GameManager &game);
  void statisticMenu(sf::RenderWindow &window, MusicManager &menuMusic);
  void configMenu(sf::RenderWindow &window, MusicManager &menuMusic);

  int height;
  int width;
  int buttonSize;
  int textSize;
  int headSize;
};
