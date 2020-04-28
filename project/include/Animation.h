//
// Created by Ivan Gorshkov on 27.04.2020.
//

#pragma once
#include <SFML/Graphics.hpp>

class Animation {
 public:
  Animation() = default;
  Animation(sf::Texture &t, int x, int y, int w, int h, int count, float speed, int step);
  void tick(float time);
  void setFlip(bool value);
  void setPlay(bool value);
  float getCurrentFrame();
  void setSpritePosition(int x, int y);
  sf::Sprite getSprite();

 private:
  std::vector<sf::IntRect> frames;
  sf::Sprite sprite;
  bool flip;
  bool is_playing;
  float speed;
  float current_frame;
  std::vector<sf::IntRect> frames_flip;
};

