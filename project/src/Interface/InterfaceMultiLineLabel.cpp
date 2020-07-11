#include "InterfaceMultiLineLabel.h"

void InterfaceMultiLineLabel::SetLine(const std::shared_ptr<InterfaceLabel>& label) {
  multiLineLabel.push_back(label);

  updateSize(label);
}

void InterfaceMultiLineLabel::CalculateLabelPosition() {
  float y = 0;

  for (auto &i : multiLineLabel) {
    float x = (width - i->GetTextRectSize().x) / 2;
    multiLineLabelPosition.emplace_back(x, y);
    y += i->GetTextRectSize().y;
  }
}

void InterfaceMultiLineLabel::SetPosition(float getX, float getY) {
  for (int i = 0; i < multiLineLabel.size(); i++) {
    multiLineLabel[i]->SetPosition(multiLineLabelPosition[i].x + getX, multiLineLabelPosition[i].y + getY);
  }
}

void InterfaceMultiLineLabel::Draw(sf::RenderWindow &window) {
  for (auto &i : multiLineLabel) {
    i->Draw(window);
  }
}

void InterfaceMultiLineLabel::updateSize(const std::shared_ptr<InterfaceLabel>& label) {
  height += label->GetTextRectSize().y;
  if (label->GetTextRectSize().x > width) {
    width = label->GetTextRectSize().x;
  }
}

