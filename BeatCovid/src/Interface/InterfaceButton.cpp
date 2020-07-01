#include "InterfaceButton.h"
#include <iostream>

InterfaceButton::InterfaceButton(const std::string &fontPath, int getSize, float getX, float getY, const std::string &str)
: InterfaceLabel(fontPath, getSize, getX, getY, str) {
}

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
