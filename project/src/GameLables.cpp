#include "GameLables.h"
#include <sstream>

GameLables::GameLables() {
  font.loadFromFile("../files/fonts/Inconsolata-Bold.ttf");
  points.setFont(font);
  points.setCharacterSize(40);
  points.setStyle(sf::Text::Bold);
  points.setColor(sf::Color::White);
}

void GameLables::DrawPlayerData(sf::RenderWindow &window, int points_int, int hp_int, unsigned int arm_int) {
  drawPoints(window, points_int);
  drawHp(window, hp_int);
  drawArm(window, arm_int);
}

void GameLables::drawPoints(sf::RenderWindow &window, int points_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  points.setPosition(center.x - size.x / 2 + 1000, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "Points: " << points_int;
  points.setString(ss.str());
  window.draw(points);
}

void GameLables::drawHp(sf::RenderWindow &window, int hp_int) {
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

void GameLables::drawArm(sf::RenderWindow &window, unsigned int arm_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  points.setPosition(center.x - size.x / 2 + 200, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "ARM: " << arm_int;
  points.setString(ss.str());
  window.draw(points);
}

void GameLables::DrawSafeTransportFuel(sf::RenderWindow &window, int fuel_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  points.setPosition(center.x - size.x / 2 + 500, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "Fuel: " << fuel_int << "%";
  points.setString(ss.str());
  window.draw(points);
}


void GameLables::DrawTransportHelp(sf::RenderWindow &window, float x, float y) {
  points.setPosition(x + 30, y - 60);
  std::ostringstream ss;
  ss << "E";
  points.setString(ss.str());
  window.draw(points);
}

void GameLables::DrawUnSafeTransportDmg(sf::RenderWindow &window, int dmg_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  points.setPosition(center.x - size.x / 2 + 500, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "Dmg: " << dmg_int;
  points.setString(ss.str());
  window.draw(points);
}

void GameLables::DrawNoVaccine(sf::RenderWindow &window) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  points.setPosition(center.x - size.x / 2 + 500, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "No vaccine";
  points.setString(ss.str());
  window.draw(points);
}
