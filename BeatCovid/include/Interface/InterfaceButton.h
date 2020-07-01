#pragma once

#include "InterfaceLabel.h"
#include <SFML/Graphics.hpp>

class InterfaceButton: public InterfaceLabel {
public:
    InterfaceButton(const std::string &fontPath, int getSize, float getX, float getY, const std::string &str);
    bool IsSelect(sf::Vector2i mouse);
};
