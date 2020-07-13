#pragma once

#include <string>
#include "InterfaceLabel.h"

class InterfaceButton : public InterfaceLabel {
 public:
  InterfaceButton(const std::string &fontPath, unsigned int getSize, const std::string &str);
  InterfaceButton(const std::string &fontPath, unsigned int getSize, float getX, float getY, const std::string &str);
  bool IsSelect(sf::Vector2i mouse);
};
