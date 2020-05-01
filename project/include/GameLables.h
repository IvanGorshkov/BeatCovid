//
// Created by Ivan Gorshkov on 01.05.2020.
//

#pragma once

#include <SFML/Graphics.hpp>

class GameLables {
 public:
  GameLables();
  void DrawPoints(sf::RenderWindow &window, int points_int);

 private:
  sf::Text points;
  sf::Font font;
};

