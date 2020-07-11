#include "InterfaceButton.h"

InterfaceButton::InterfaceButton(const std::string &fontPath, unsigned int getSize, const std::string &str)
    : InterfaceLabel(fontPath, getSize, str) {
}

InterfaceButton::InterfaceButton(const std::string &fontPath, unsigned int getSize, float getX, float getY, const std::string &str)
    : InterfaceLabel(fontPath, getSize, getX, getY, str) {
}

bool InterfaceButton::IsSelect(sf::Vector2i mouse) {
  if (sf::IntRect(x, y, width, height).contains(mouse)) {
    text.setFillColor(sf::Color::Red);

    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
  } else {
    text.setFillColor(sf::Color::White);

    return false;
  }
}
