#pragma once

#include <SFML/Graphics.hpp>

class InterfaceSprite {
 public:
  explicit InterfaceSprite(const std::string &texturePath, float x, float y);
  explicit InterfaceSprite(const std::string &texturePath);
  void SetColor(sf::Color color);
  sf::Rect<int> GetTextureRect();
    sf::Vector2f GetSpriteRect();
  void Size(float w, float h);
  sf::Vector2<int> GetSize();
  void SetTextureRect(sf::Rect<int> rect);
  void SetPosition(float x, float y);
  void Draw(sf::RenderWindow &window);

 private:
  sf::Texture texture;
  sf::Sprite sprite;
    int w;
    int h;
};
