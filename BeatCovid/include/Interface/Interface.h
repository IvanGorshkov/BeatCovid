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

#define BACK_BUTTON_SHIFT 31

class Interface {
 public:
  static Interface &GetInstance(sf::RenderWindow &window);
  void MainMenu(sf::RenderWindow &window);
  void PenaltyPolice(sf::RenderWindow &window);
  void DiedPolice(sf::RenderWindow &window);

 private:
  explicit Interface(sf::RenderWindow &window);
  ~Interface() = default;
  Interface(const Interface &);
  Interface &operator=(const Interface &);

  void newGameWarningMenu(sf::RenderWindow &window, MusicManager &menuMusic, Save &save);
  bool startNewGame(sf::RenderWindow &window, Save &save, MusicManager &menuMusic);
  bool winMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic);
  bool nextLvlMenu(sf::RenderWindow &window, Save &save, GameManager &game, MusicManager &menuMusic);
  bool diedMenu(sf::RenderWindow &window, GameManager &game);

  void statisticMenu(sf::RenderWindow &window, MusicManager &menuMusic);
  void configMenu(sf::RenderWindow &window, MusicManager &menuMusic);

  bool gameMenu(sf::RenderWindow &window, GameManager &game, MusicManager &menuMusic);
  bool shopMenu(sf::RenderWindow &window, Save &save);
  void buy(std::vector<int> arm_vector, int index);
  bool aboutMenu(sf::RenderWindow &window, MusicManager &menuMusic);

  int height;
  int width;
  int buttonSize;
  int textSize;
  int headSize;
};
