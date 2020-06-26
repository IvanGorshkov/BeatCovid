#include "InterfaceText.h"
#include <sstream>

InterfaceText::InterfaceText(const std::string& fontPath, int size, float x, float y) {
  font.loadFromFile(FILES_PATH"files/fonts/Inconsolata-Bold.ttf");

  text.setFont(font);
  text.setCharacterSize(size);
  text.setStyle(sf::Text::Bold);
  text.setFillColor(sf::Color::White);

  text.setPosition(x, y);
}

InterfaceText::InterfaceText(const std::string &fontPath, int size, float x, float y, std::ostringstream &ss) {
  font.loadFromFile(FILES_PATH"files/fonts/Inconsolata-Bold.ttf");

  text.setFont(font);
  text.setCharacterSize(size);
  text.setStyle(sf::Text::Bold);
  text.setFillColor(sf::Color::White);

  text.setPosition(x, y);

  text.setString(ss.str());
}

void InterfaceText::SetText(std::ostringstream &ss) {
  text.setString(ss.str());
}

void InterfaceText::Draw(sf::RenderWindow &window) {
  window.draw(text);
}

