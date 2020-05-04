#pragma once

#include <SFML/Graphics.hpp>

class GameLables {
 public:
  GameLables();
  void DrawPoints(sf::RenderWindow &window, int points_int);
  void DrawHp(sf::RenderWindow &window,   int hp_int);
  void DrawArm(sf::RenderWindow &window,  unsigned int arm_int);

 private:
  sf::Text points;
  sf::Font font;
};

