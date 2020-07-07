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

sf::Vector2f InterfaceSprite::GetSpriteRect() {
    return sprite.getPosition();
}

sf::Vector2<int> InterfaceSprite::GetSize() {
    return sf::Vector2<int>(w,h);
}

void InterfaceSprite::Size(float w, float h) {
  //sprite.setScale(l, r);
  sf::Vector2f targetSize(w, h);
    this->w = w;
    this->h = h;
  sprite.setScale(
      targetSize.x / sprite.getLocalBounds().width,
      targetSize.y / sprite.getLocalBounds().height);
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
