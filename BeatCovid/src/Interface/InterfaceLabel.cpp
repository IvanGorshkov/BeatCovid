#include "InterfaceLabel.h"
#include <iostream>

InterfaceLabel::InterfaceLabel(const std::string& fontPath, int getSize)
: size(getSize) {
    
  font.loadFromFile(fontPath);

  text.setFont(font);
  text.setCharacterSize(size);
  text.setStyle(sf::Text::Bold);
  text.setFillColor(sf::Color::White);
}

InterfaceLabel::InterfaceLabel(const std::string& fontPath, int getSize, const std::string &str)
: InterfaceLabel(fontPath, getSize) {
    
    this->str = str;
    text.setString(str);
    getLocalSize();
}

InterfaceLabel::InterfaceLabel(const std::string& fontPath, int getSize, float getX, float getY)
: InterfaceLabel(fontPath, getSize) {

    x = getX;
    y = getY;
}

InterfaceLabel::InterfaceLabel(const std::string &fontPath, int getSize, float getX, float getY, const std::string &str)
: InterfaceLabel(fontPath, getSize, getX, getY) {
         
  this->str = str;
  text.setString(str);
  getLocalSize();
}

void InterfaceLabel::SetText(const std::string &str) {
  text.setString(str);
  getLocalSize();
}

void InterfaceLabel::SetPosition(float getX, float getY) {
    x = getX;
    y = getY;
}

sf::Vector2f InterfaceLabel::GetTextRectSize() {
    return sf::Vector2f(width, height);
}

void InterfaceLabel::Draw(sf::RenderWindow &window) {
  text.setPosition(x, y);
  window.draw(text);
}

void InterfaceLabel::getLocalSize() {
    const sf::String str = text.getString() + '\n';

    float maxLineWidth = 0.f;
    float lineWidth = 0.f;
    unsigned int lines = 0;

    for (sf::String::ConstIterator itr = str.begin(); itr != str.end(); ++itr) {
                if (*itr == '\n') {
                        ++lines;
                        maxLineWidth = std::max(maxLineWidth, lineWidth);
                        lineWidth = 0.f;
                }
                else {
                    lineWidth += text.getFont()->getGlyph(*itr, text.getCharacterSize(), text.getStyle() & sf::Text::Bold).advance;
                }
        }

    const float lineHeight = static_cast<float>(text.getFont()->getLineSpacing(text.getCharacterSize()));
    
    height = lines * lineHeight;
    width = maxLineWidth;
}

