#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

class InterfaceLabel {
 public:
  explicit InterfaceLabel(const std::string &fontPath, int getSize);
  explicit InterfaceLabel(const std::string &fontPath, int getSize, const std::string &str);
  explicit InterfaceLabel(const std::string &fontPath, int getSize, float getX, float getY);
  explicit InterfaceLabel(const std::string &fontPath, int getSize, float getX, float getY, const std::string &str);
  void SetText(const std::string &str);
  void SetPosition(float getX, float getY);
  sf::Vector2f GetTextRectSize();
  void Draw(sf::RenderWindow &window);

 protected:
  void getLocalSize();
    
  sf::Font font;
  std::string str;
  float x;
  float y;
  int size;
  int height;
  int width;
  sf::Text text;
};
