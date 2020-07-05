#pragma once

#include "InterfaceLabel.h"
#include "InterfaceButton.h"
#include "InterfaceMultiLineLabel.h"
#include <memory>

class InterfaceTable {
 public:
  explicit InterfaceTable() = default;

  void SetCenterLabel(const std::shared_ptr<InterfaceLabel> &label);
  void SetLeftLabel(const std::shared_ptr<InterfaceLabel> &label);
  void SetRightLabel(const std::shared_ptr<InterfaceLabel> &label);

  void SetCenterButton(const std::shared_ptr<InterfaceButton> &button);
  void SetLeftButton(const std::shared_ptr<InterfaceButton> &button);
  void SetRightButton(const std::shared_ptr<InterfaceButton> &button);

  std::vector<std::shared_ptr<InterfaceButton>> GetCenterButtons();
  std::vector<std::shared_ptr<InterfaceButton>> GetLeftButtons();
  std::vector<std::shared_ptr<InterfaceButton>> GetRightButtons();

  void CalculateTablePosition();
  void SetPosition(int height, int width);
  void Draw(sf::RenderWindow &window);

 private:
  void calculateCenterLabel();
  void calculateCenterButton();
  void calculateLeftRightLabel();
  void calculateLeftRightButton();

  std::vector<std::shared_ptr<InterfaceLabel>> centerLabel;
  std::vector<sf::Vector2i> centerLabelPosition;
  int centerLabelMaxWidth = 0;
  int centerLabelHeight = 0;

  std::vector<std::shared_ptr<InterfaceButton>> centerButton;
  std::vector<sf::Vector2i> centerButtonPosition;
  int centerButtonMaxWidth = 0;
  int centerButtonHeight = 0;

  std::vector<std::shared_ptr<InterfaceLabel>> leftLabel;
  std::vector<std::shared_ptr<InterfaceLabel>> rightLabel;
  std::vector<sf::Vector2i> leftLabelPosition;
  std::vector<sf::Vector2i> rightLabelPosition;
  int leftLabelMaxWidth = 0;
  int rightLabelMaxWidth = 0;
  int leftLabelHeight = 0;
  int rightLabelHeight = 0;

  std::vector<std::shared_ptr<InterfaceButton>> leftButton;
  std::vector<std::shared_ptr<InterfaceButton>> rightButton;
  std::vector<sf::Vector2i> leftButtonPosition;
  std::vector<sf::Vector2i> rightButtonPosition;
  int leftButtonMaxWidth = 0;
  int rightButtonMaxWidth = 0;
  int leftButtonHeight = 0;
  int rightButtonHeight = 0;
};
