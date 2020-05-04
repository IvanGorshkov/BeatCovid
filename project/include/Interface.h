#pragma once

#include <SFML/Graphics.hpp>

class Interface {
 public:
  Interface() = default;
  static void MainMenu();
  static void Pause();
  static void StartGame(sf::RenderWindow *window);
};
