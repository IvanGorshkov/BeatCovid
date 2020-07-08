#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "SaveGame.h"
#include "MusicManager.h"
#include "InterfaceLabel.h"
#include "InterfaceImage.h"
#include "InterfaceButton.h"
#include "InterfaceTable.h"

#define BACK_BUTTON_SHIFT 30

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

  void newGameWarningMenu(sf::RenderWindow &window, MusicManager &music);
  void startNewGame(sf::RenderWindow &window, MusicManager &music);
  bool winMenu(sf::RenderWindow &window, MusicManager &music, bool isLoadFromMenu);
  bool nextLvlMenu(sf::RenderWindow &window, MusicManager &music);
  bool diedMenu(sf::RenderWindow &window, MusicManager &music);

  void statisticMenu(sf::RenderWindow &window);
  void configMenu(sf::RenderWindow &window);

  bool gameMenu(sf::RenderWindow &window, MusicManager &music, std::vector<int> data);
  bool shopMenu(sf::RenderWindow &window);

  void aboutMenu(sf::RenderWindow &window);

  unsigned int height;
  unsigned int width;
  unsigned int buttonSize;
  unsigned int textSize;
  unsigned int headSize;
};
