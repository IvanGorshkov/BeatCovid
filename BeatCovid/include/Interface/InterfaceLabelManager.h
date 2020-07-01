#pragma once

#include "InterfaceLabel.h"

class InterfaceLabelManager {
public:
 explicit InterfaceLabelManager() = default;
 void SetLeft(const InterfaceLabel &label);
 void SetRight(const InterfaceLabel &label);
 void CalculatePosition(float height, float width);
 void Draw(sf::RenderWindow &window);
    
private:
 std::vector<InterfaceLabel> left;
 std::vector<InterfaceLabel> right;
};
