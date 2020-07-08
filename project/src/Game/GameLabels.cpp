#include "GameLabels.h"
#include "ResourcePath.hpp"
#include <sstream>

GameLabels::GameLabels() {
  font.loadFromFile(resourcePath() + "files/fonts/Inconsolata-Bold.ttf");
  text.setFont(font);
  text.setStyle(sf::Text::Bold);
  text.setFillColor(sf::Color::White);
}

void GameLabels::DrawPlayerData(sf::RenderWindow &window, int points_int, int hp_int, unsigned int arm_int, bool vaccine) {
  int height = window.getSize().y;
  int width = window.getSize().x;
  int textSize = window.getSize().y / 30;
  text.setCharacterSize(textSize);
    
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
    
  float xPosition = center.x - size.x / 2;
  float yPosition = center.y - size.y / 2;
    
  std::ostringstream ss;
  if (hp_int < 0) {
    hp_int = 0;
  }
  ss << "HP: " << hp_int << "%" << " ARM: " << arm_int << " Vaccine: " << vaccine;
  text.setPosition(xPosition + 10, yPosition  + 13);
  text.setString(ss.str());
  window.draw(text);
    
  drawPoints(window, points_int);
}

void GameLabels::drawPoints(sf::RenderWindow &window, int points_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  text.setPosition(center.x - size.x / 2 + 1000, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "Points: " << points_int;
  text.setString(ss.str());
  window.draw(text);
}

void GameLabels::drawHp(sf::RenderWindow &window, int hp_int) {
  
}

void GameLabels::drawArm(sf::RenderWindow &window, unsigned int arm_int) {
}

void GameLabels::drawVaccine(sf::RenderWindow &window, bool vaccine) {
}

void GameLabels::DrawSafeTransportFuel(sf::RenderWindow &window, int fuel_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  text.setPosition(center.x - size.x / 2 + 600, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "Fuel: " << fuel_int << "%";
  text.setString(ss.str());
  window.draw(text);
}

void GameLabels::DrawTransportHelp(sf::RenderWindow &window, float x, float y) {
  text.setPosition(x + 30, y - 60);
  std::ostringstream ss;
  ss << "E";
  text.setString(ss.str());
  window.draw(text);
}

void GameLabels::DrawUnSafeTransportDmg(sf::RenderWindow &window, int dmg_int) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  text.setPosition(center.x - size.x / 2 + 600, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "Dmg: " << dmg_int;
  text.setString(ss.str());
  window.draw(text);
}

void GameLabels::DrawNoVaccine(sf::RenderWindow &window) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  text.setPosition(center.x - size.x / 2 + 600, center.y - size.y / 2 + 13);
  std::ostringstream ss;
  ss << "No vaccine";
  text.setString(ss.str());
  window.draw(text);
}

void GameLabels::DrawFPS(sf::RenderWindow &window, int fps) {
  sf::Vector2f center = window.getView().getCenter();
  sf::Vector2f size = window.getView().getSize();
  text.setPosition(center.x - size.x / 2 + 600, center.y - size.y / 2 + 1300);
  std::ostringstream ss;
  ss << fps;
  text.setString(ss.str());
  window.draw(text);
}
