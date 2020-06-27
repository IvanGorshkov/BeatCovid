#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

class InterfaceLabel {
 public:
  explicit InterfaceLabel(const std::string &fontPath, int getSize, float getX, float getY);
  explicit InterfaceLabel(const std::string &fontPath, int getSize, float getX, float getY, const std::string &str);
  explicit InterfaceLabel(const std::string &fontPath, int getSize, float getX, float getY, const std::ostringstream &ss);
  void SetText(const std::ostringstream &ss);
  void SetText(const std::string &str);
  virtual void Update(sf::RenderWindow &window);
  void Draw(sf::RenderWindow &window);

 protected:
  sf::Font font;
  std::string str;
  float x;
  float y;
  int size;
  int defaultSize;
  sf::Text text;
};
