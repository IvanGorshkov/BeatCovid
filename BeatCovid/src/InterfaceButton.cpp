#include "InterfaceButton.h"
#include <iostream>

InterfaceButton::InterfaceButton(const std::string &fontPath, int getSize, float getX, float getY, const std::string &str)
: InterfaceLabel(fontPath, getSize, getX, getY, str) {
}

//InterfaceButton::InterfaceButton(const std::string &fontPath, int getSize)
//: InterfaceLabel(fontPath, getSize) {
//}
//
//InterfaceButton::InterfaceButton(const std::string &fontPath, int getSize, const std::string &str)
//: InterfaceLabel(fontPath, getSize, str) {
//}

bool InterfaceButton::IsSelect(sf::Vector2i mouse) {
    if((mouse.x > x && mouse.x < x + width) && (mouse.y > y && mouse.y < y + height)){
        text.setFillColor(sf::Color::Red);
        
//        std::cout << "Mouse Position X: " << mouse.x << std::endl;
//        std::cout << "Mouse Position Y: " << mouse.y << std::endl;
//
//        std::cout << "Button Position X: " << x << std::endl;
//        std::cout << "Button Position Y: " << y << std::endl;
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return true;
        }
        
        return  false;
    } else {
        text.setFillColor(sf::Color::White);
        return false;
    }
}

//void InterfaceButton::Draw(sf::RenderWindow &window) {
//    text.setPosition(x, y);
//    
//    text.setString(str);
//
//    window.draw(text);
//}


void InterfaceButton::Update(sf::RenderWindow &window) {
    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();

    x = center.x - size.x / 2 + x;
    y = center.y - size.y / 2 + y;

    width = text.getLocalBounds().width;
    height = this->size;

//    std::cout << "X: " << x << std::endl;
//    std::cout << "Y: " << y << std::endl;
//    std::cout << "Width: " << width << std::endl;
//    std::cout << "Height: " << height << std::endl;
}
