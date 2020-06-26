#pragma once

#include <SFML/Graphics.hpp>

class InterfaceSprite {
 public:
  explicit InterfaceSprite(const std::string &texturePath, float x, float y);
  explicit InterfaceSprite(const std::string &texturePath);
  void SetColor(sf::Color color);
  sf::Rect<int> GetTextureRect();
  void Scale(float l, float r);
  void SetTextureRect(sf::Rect<int> rect);
  void SetPosition(float x, float  y);
  void Draw(sf::RenderWindow &window);

 private:
  sf::Texture texture;
  sf::Sprite sprite;
};