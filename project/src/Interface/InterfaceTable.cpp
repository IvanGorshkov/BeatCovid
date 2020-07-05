#include "InterfaceTable.h"
#include <iostream>

void InterfaceTable::SetCenterLabel(const std::shared_ptr<InterfaceLabel> &label) {
  centerLabel.push_back(label);
}

void InterfaceTable::SetLeftLabel(const std::shared_ptr<InterfaceLabel> &label) {
  leftLabel.push_back(label);
}

void InterfaceTable::SetRightLabel(const std::shared_ptr<InterfaceLabel> &label) {
  rightLabel.push_back(label);
}

void InterfaceTable::SetCenterButton(const std::shared_ptr<InterfaceButton> &button) {
  centerButton.push_back(button);
}

void InterfaceTable::SetLeftButton(const std::shared_ptr<InterfaceButton> &button) {
  leftButton.push_back(button);
}

void InterfaceTable::SetRightButton(const std::shared_ptr<InterfaceButton> &button) {
  rightButton.push_back(button);
}

std::vector<std::shared_ptr<InterfaceButton>> InterfaceTable::GetCenterButtons() {
  return centerButton;
}

std::vector<std::shared_ptr<InterfaceButton>> InterfaceTable::GetLeftButtons() {
  return leftButton;
}

std::vector<std::shared_ptr<InterfaceButton>> InterfaceTable::GetRightButtons() {
  return rightButton;
}

void InterfaceTable::CalculateTablePosition() {
  if (!centerLabel.empty()) {
    calculateCenterLabel();
  }

  if (!centerButton.empty()) {
    calculateCenterButton();
  }

  if (!leftLabel.empty() && !rightLabel.empty()) {
    calculateLeftRightLabel();
  }

  if (!leftButton.empty() && !rightButton.empty()) {
    calculateLeftRightButton();
  }
}

void InterfaceTable::calculateCenterLabel() {
  for (auto &i: centerLabel) {
    centerLabelHeight += i->GetTextRectSize().y;

    if (i->GetTextRectSize().x > centerLabelMaxWidth) {
      centerLabelMaxWidth = i->GetTextRectSize().x;
    }
  }

  centerLabelHeight += centerLabel[centerLabel.size() - 1]->GetTextRectSize().y;

  float y = 0;
  for (auto &i: centerLabel) {
    float x = (centerLabelMaxWidth - i->GetTextRectSize().x) / 2;
    centerLabelPosition.emplace_back(x, y);
    y += i->GetTextRectSize().y;
  }
}

void InterfaceTable::calculateCenterButton() {
  for (auto &i: centerButton) {
    centerButtonHeight += i->GetTextRectSize().y * 2;

    if (i->GetTextRectSize().x > centerButtonMaxWidth) {
      centerButtonMaxWidth = i->GetTextRectSize().x;
    }
  }

  float y = 0;
  for (auto &i: centerButton) {
    float x = (centerButtonMaxWidth - i->GetTextRectSize().x) / 2;
    centerButtonPosition.emplace_back(x, y);
    y += i->GetTextRectSize().y * 2;
  }
}

void InterfaceTable::calculateLeftRightLabel() {
  for (auto &i: leftLabel) {
    leftLabelHeight += i->GetTextRectSize().y * 2;

    if (i->GetTextRectSize().x > leftLabelMaxWidth) {
      leftLabelMaxWidth = i->GetTextRectSize().x;
    }
  }

  leftLabelHeight -= leftLabel[leftLabel.size() - 1]->GetTextRectSize().y;

  for (auto &i: rightLabel) {
    rightLabelHeight += i->GetTextRectSize().y * 2;

    if (i->GetTextRectSize().x > rightLabelMaxWidth) {
      rightLabelMaxWidth = i->GetTextRectSize().x;
    }
  }

  rightLabelHeight -= rightLabel[rightLabel.size() - 1]->GetTextRectSize().y;

  float y = 0;
  for (auto &i: leftLabel) {
    leftLabelPosition.emplace_back(0, y);
    y += i->GetTextRectSize().y * 2;
  }

  y = 0;
  for (auto &i: rightLabel) {
    rightLabelPosition.emplace_back(0, y);
    y += i->GetTextRectSize().y * 2;
  }
}

void InterfaceTable::calculateLeftRightButton() {
  for (auto &i: leftButton) {
    leftButtonHeight += i->GetTextRectSize().y * 2;

    if (i->GetTextRectSize().x > leftButtonMaxWidth) {
      leftButtonMaxWidth = i->GetTextRectSize().x;
    }
  }

  leftButtonHeight -= leftButton[leftButton.size() - 1]->GetTextRectSize().y;

  for (auto &i: rightButton) {
    rightButtonHeight += i->GetTextRectSize().y * 2;

    if (i->GetTextRectSize().x > rightButtonMaxWidth) {
      rightButtonMaxWidth = i->GetTextRectSize().x;
    }
  }

  rightButtonHeight -= rightButton[rightButton.size() - 1]->GetTextRectSize().y;

  float y = 0;
  for (auto &i: leftButton) {
    leftButtonPosition.emplace_back(i->GetTextRectSize().x, y);
    y += i->GetTextRectSize().y * 2;
  }

  y = 0;
  for (auto &i: rightButton) {
    rightButtonPosition.emplace_back(-i->GetTextRectSize().x, y);
    y += i->GetTextRectSize().y * 2;
  }
}

void InterfaceTable::SetPosition(int height, int width) {
  int upPosition = (height
      - centerLabelHeight
      - centerButtonHeight
      - std::max(leftLabelHeight, rightButtonHeight)
      - std::max(leftButtonHeight, rightButtonHeight)) / 2;

  int centerLabelXPosition = 0;
  int centerButtonXPosition = 0;
  int leftLabelXPosition = 0;
  int rightLabelXPosition = 0;
  int leftButtonXPosition = 0;
  int rightButtonXPosition = 0;

  if (!centerLabel.empty()) {
    centerLabelXPosition = (width - centerLabelMaxWidth) / 2;
  }

  if (!centerButton.empty()) {
    centerButtonXPosition = (width - centerButtonMaxWidth) / 2;
  }

  if (!leftLabel.empty() && !rightLabel.empty()) {
    leftLabelXPosition = (width - leftLabelMaxWidth - rightLabelMaxWidth) / 3;
    rightLabelXPosition = (width - leftLabelMaxWidth - rightLabelMaxWidth) / 3 * 2 + leftLabelMaxWidth;
  }

  if (!leftButton.empty() && !rightButton.empty()) {
    leftButtonXPosition = (width - leftButtonMaxWidth - rightButtonMaxWidth) / 3;
    rightButtonXPosition = (width - leftButtonMaxWidth - rightButtonMaxWidth) / 3 * 2 + leftButtonMaxWidth;
  }

  std::cout << "Height : " << height << std::endl;
  std::cout << "Width : " << width << std::endl << std::endl << std::endl;

  std::cout << "centerLabelMaxWidth : " << centerLabelMaxWidth << std::endl;
  std::cout << "centerLabelHeight : " << centerLabelHeight << std::endl << std::endl;
  std::cout << "centerButtonMaxWidth : " << centerButtonMaxWidth << std::endl;
  std::cout << "centerButtonHeight : " << centerButtonHeight << std::endl << std::endl;
  std::cout << "leftLabelMaxWidth : " << leftLabelMaxWidth << std::endl;
  std::cout << "leftLabelHeight : " << leftLabelHeight << std::endl << std::endl;
  std::cout << "rightLabelMaxWidth : " << rightLabelMaxWidth << std::endl;
  std::cout << "rightLabelHeight : " << rightLabelHeight << std::endl << std::endl;
  std::cout << "leftButtonMaxWidth : " << leftButtonMaxWidth << std::endl;
  std::cout << "leftButtonHeight : " << leftButtonHeight << std::endl << std::endl;
  std::cout << "rightButtonMaxWidth : " << rightButtonMaxWidth << std::endl;
  std::cout << "rightButtonHeight : " << rightButtonHeight << std::endl << std::endl << std::endl;

  std::cout << "upPosition : " << upPosition << std::endl << std::endl;
  std::cout << "centerLabelXPosition : " << centerLabelXPosition << std::endl;
  std::cout << "centerButtonXPosition : " << centerButtonXPosition << std::endl << std::endl;
  std::cout << "leftLabelXPosition : " << leftLabelXPosition << std::endl;
  std::cout << "rightLabelXPosition : " << rightLabelXPosition << std::endl << std::endl;
  std::cout << "leftButtonXPosition : " << leftButtonXPosition << std::endl;
  std::cout << "rightButtonXPosition : " << rightButtonXPosition << std::endl << std::endl;

  for (int i = 0; i < centerLabel.size(); i++) {
    centerLabel[i]->SetPosition(centerLabelPosition[i].x + centerLabelXPosition,
                                centerLabelPosition[i].y + upPosition);
  }
  upPosition += centerLabelHeight;

  for (int i = 0; i < centerButton.size(); i++) {
    centerButton[i]->SetPosition(centerButtonPosition[i].x + centerButtonXPosition,
                                 centerButtonPosition[i].y + upPosition);
  }
  upPosition += centerButtonHeight;

  for (int i = 0; i < leftLabel.size(); i++) {
    leftLabel[i]->SetPosition(leftLabelPosition[i].x + leftLabelXPosition,
                              leftLabelPosition[i].y + upPosition);
  }

  for (int i = 0; i < rightLabel.size(); i++) {
    rightLabel[i]->SetPosition(rightLabelPosition[i].x + rightLabelXPosition,
                               rightLabelPosition[i].y + upPosition);
  }
  upPosition += std::max(leftLabelHeight, rightButtonHeight);

  for (int i = 0; i < leftButton.size(); i++) {
    leftButton[i]->SetPosition(leftButtonPosition[i].x + leftButtonXPosition,
                               leftButtonPosition[i].y + upPosition);
  }

  for (int i = 0; i < rightButton.size(); i++) {
    rightButton[i]->SetPosition(rightButtonPosition[i].x + rightButtonXPosition,
                                rightButtonPosition[i].y + upPosition);
  }
}

void InterfaceTable::Draw(sf::RenderWindow &window) {
  for (auto &i: centerLabel) {
    i->Draw(window);
  }

  for (auto &i: centerButton) {
    i->Draw(window);
  }

  for (auto &i: leftLabel) {
    i->Draw(window);
  }

  for (auto &i: rightLabel) {
    i->Draw(window);
  }

  for (auto &i: leftButton) {
    i->Draw(window);
  }

  for (auto &i: rightButton) {
    i->Draw(window);
  }
}
