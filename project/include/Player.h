//
// Created by Ivan Gorshkov on 25.04.2020.
//

#pragma once
#include <SFML/Graphics.hpp>

class Player {
 public:
  explicit Player(sf::Texture &image);
  sf::Sprite getSprite();
  void move(float dx);
  void jump();
  void status(float offsetX, std::string *TileMap);
  sf::FloatRect getRect();
  void collision (int num, std::string *TileMap);
 private:

  int hp;
  int  arm;
  int points;
  bool isGround;
  bool isJump;
  float dx;
  float dy;
  float jumphight;
  float currentFrame;
  sf::FloatRect rect;
  sf::Sprite sprite;
};
