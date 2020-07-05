#pragma once

#include "InterfaceLabel.h"
#include <memory>

class InterfaceMultiLineLabel {
 public:
  explicit InterfaceMultiLineLabel() = default;
  void SetLine(const std::shared_ptr<InterfaceLabel>& label);
  void CalculateLabelPosition();
  void SetPosition(float getX, float getY);
  void Draw(sf::RenderWindow &window);

 private:
  void updateSize(const std::shared_ptr<InterfaceLabel>& label);

  int height = 0;
  int width = 0;
  std::vector<std::shared_ptr<InterfaceLabel>> multiLineLabel;
  std::vector<sf::Vector2i> multiLineLabelPosition;
};
