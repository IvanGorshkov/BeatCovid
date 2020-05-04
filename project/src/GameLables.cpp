#include "GameLables.h"
#include <sstream>

GameLables::GameLables() {
  font.loadFromFile("../files/Inconsolata-Bold.ttf");
  points.setFont(font);
  points.setCharacterSize(40);
  points.setStyle(sf::Text::Bold);
  points.setColor(sf::Color::White);
}

void GameLables::DrawPoints(sf::RenderWindow &window, int points_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  points.setPosition(center.x - size.x / 2 + 1000, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "Points: " << points_int;
  points.setString(ss.str());
  window.draw(points);
}

void GameLables::DrawHp(sf::RenderWindow &window,  int hp_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  points.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  if (hp_int < 0) {
    hp_int = 0;
  }
  ss << "HP: " << hp_int << "%";
  points.setString(ss.str());
  window.draw(points);
}

void GameLables::DrawArm(sf::RenderWindow &window, unsigned int arm_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  points.setPosition(center.x - size.x / 2 + 200, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "ARM: " << arm_int;
  points.setString(ss.str());
  window.draw(points);
}
