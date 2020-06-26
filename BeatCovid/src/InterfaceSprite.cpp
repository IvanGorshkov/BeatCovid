#include "InterfaceSprite.h"

InterfaceSprite::InterfaceSprite(const std::string &texturePath, float x, float y) {
  texture.loadFromFile(texturePath);

  sprite.setTexture(texture);

  sprite.setPosition(x, y);
}

InterfaceSprite::InterfaceSprite(const std::string &texturePath) {
  texture.loadFromFile(texturePath);

  sprite.setTexture(texture);
}

void InterfaceSprite::SetColor(sf::Color color) {
  sprite.setColor(color);
}

sf::Rect<int> InterfaceSprite::GetTextureRect() {
  return sprite.getTextureRect();
}

void InterfaceSprite::Scale(float l, float r) {
  sprite.scale(l, r);
}

void InterfaceSprite::SetTextureRect(sf::Rect<int> rect) {
  sprite.setTextureRect(rect);
}

void InterfaceSprite::SetPosition(float x, float y) {
  sprite.setPosition(x, y);
}

void InterfaceSprite::Draw(sf::RenderWindow &window) {
  window.draw(sprite);
}