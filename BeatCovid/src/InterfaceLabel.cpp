#include "InterfaceLabel.h"
#include <iostream>

//InterfaceLabel::InterfaceLabel(const std::string& fontPath, int getSize)
//    : size(getSize) {
//
//  font.loadFromFile(fontPath);
//
//  text.setFont(font);
//  text.setCharacterSize(size);
//  text.setStyle(sf::Text::Bold);
//  text.setFillColor(sf::Color::White);
//}

InterfaceLabel::InterfaceLabel(const std::string& fontPath, int getSize, float getX, float getY)
    :x(getX),
     y(getY),
     size(getSize),
     defaultSize(getSize) {

  font.loadFromFile(fontPath);

  text.setFont(font);
  text.setCharacterSize(size);
  text.setStyle(sf::Text::Bold);
  text.setFillColor(sf::Color::White);

  text.setPosition(x, y);
}

InterfaceLabel::InterfaceLabel(const std::string &fontPath, int getSize, float getX, float getY, const std::string &str)
    :x(getX),
     y(getY),
     size(getSize),
     defaultSize(getSize),
     str(str) {
         
  font.loadFromFile(fontPath);

  text.setFont(font);
  text.setCharacterSize(size);
  text.setStyle(sf::Text::Bold);
  text.setFillColor(sf::Color::White);
}

//InterfaceLabel::InterfaceLabel(const std::string &fontPath, int getSize, const std::string &str)
//    : size(getSize),
//     str(str) {
//  font.loadFromFile(fontPath);
//
//  text.setFont(font);
//  text.setCharacterSize(size);
//  text.setStyle(sf::Text::Bold);
//  text.setFillColor(sf::Color::White);
//}

InterfaceLabel::InterfaceLabel(const std::string &fontPath, int getSize, float getX, float getY, const std::ostringstream &ss)
    :x(getX),
     y(getY),
     size(getSize),
     defaultSize(getSize),
     str(ss.str()) {

  font.loadFromFile(fontPath);

  text.setFont(font);
  text.setCharacterSize(size);
  text.setStyle(sf::Text::Bold);
  text.setFillColor(sf::Color::White);
}

void InterfaceLabel::SetText(const std::ostringstream &ss) {
  text.setString(ss.str());
}

void InterfaceLabel::SetText(const std::string &str) {
  text.setString(str);
}

void InterfaceLabel::Update(sf::RenderWindow &window) {    
    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();
    
    x = center.x - size.x / 2 + x;
    y = center.y - size.y / 2 + y;
}

void InterfaceLabel::Draw(sf::RenderWindow &window) {
  text.setPosition(x, y);
  text.setString(str);
  window.draw(text);
}

