#pragma once

#include <SFML/Graphics.hpp>

class GameLabels {
 public:
  GameLabels();
  void DrawPlayerData(sf::RenderWindow &window, int points_int, int hp_int, unsigned int arm_int, bool vaccine);
  void DrawTransportHelp(sf::RenderWindow &window, float x, float y);
  void DrawSafeTransportFuel(sf::RenderWindow &window, int fuel_int);
  void DrawUnSafeTransportDmg(sf::RenderWindow &window, int dmg_int);
  void DrawNoVaccine(sf::RenderWindow &window);
  void DrawFPS(sf::RenderWindow &window, int fps);

 private:
  void drawPoints(sf::RenderWindow &window, int points_int);
  void drawHp(sf::RenderWindow &window, int hp_int);
  void drawArm(sf::RenderWindow &window, unsigned int arm_int);
  void drawVaccine(sf::RenderWindow &window, bool vaccine);
    
  sf::Text text;
  sf::Font font;
};
