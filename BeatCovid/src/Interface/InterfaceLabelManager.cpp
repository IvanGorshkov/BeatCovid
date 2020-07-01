#include "InterfaceLabelManager.h"
#include <iostream>

void InterfaceLabelManager::SetLeft(const InterfaceLabel &label) {
    left.push_back(label);
}

void InterfaceLabelManager::SetRight(const InterfaceLabel &label) {
    right.push_back(label);
}

void InterfaceLabelManager::CalculatePosition(float height, float width) {
    int leftMax = 0;
    int rightMax = 0;
    
    for (auto &i: left) {
        if (i.GetTextRectSize().x > leftMax) {
            leftMax = i.GetTextRectSize().x;
        }
    }
    
    for (auto &i: right) {
        if (i.GetTextRectSize().x > rightMax) {
            rightMax = i.GetTextRectSize().x;
        }
    }
    
    
    float leftP = (height - leftMax - rightMax) / 3;
    float rightP = (height - leftMax - rightMax) / 3 * 2 + leftMax;
    float yP = left[0].GetTextRectSize().y * 2;
    float upY = (width - (left.size() - 1) * yP) / 2;
    
    float y = upY;
    for (auto &i: left) {
        i.SetPosition(leftP, y);
        y += yP;
    }
    
    
    y = upY;
    for (auto &i: right) {
        i.SetPosition(rightP, y);
        y += yP;
    }
}

void InterfaceLabelManager::Draw(sf::RenderWindow &window) {
    for (auto &i: left) {
        i.Draw(window);
    }
    
    for (auto &i: right) {
        i.Draw(window);
    }
}
