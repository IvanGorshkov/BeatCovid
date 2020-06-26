#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

class InterfaceText {
 public:
  explicit InterfaceText(const std::string &fontFile, int size, float x, float y);
  explicit InterfaceText(const std::string &fontFile, int size, float x, float y, std::ostringstream &ss);
  void SetText(std::ostringstream &ss);
  void Draw(sf::RenderWindow &window);

 private:
  sf::Text text;
  sf::Font font;
};