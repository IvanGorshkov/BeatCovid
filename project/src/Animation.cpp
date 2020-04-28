//
// Created by Ivan Gorshkov on 27.04.2020.
//

#include "Animation.h"

Animation::Animation(sf::Texture &t, int x, int y, int w, int h, int count, float speed, int step) {
  this->speed = speed;
  sprite.setTexture(t);
  sprite.setOrigin(0,h);
  current_frame = 0;
  is_playing = true;
  flip = false;
  for (int kI = 0; kI < count; ++kI) {
    frames.push_back(sf::IntRect(x + kI*step, y, w, h));
    frames_flip.push_back(sf::IntRect(x + kI*step + w, y, -w, h));
  }
}

void Animation::tick(float time) {
  if (!is_playing) {
    return;
  }
  current_frame += speed * time;
  if (current_frame > frames.size()) {
    current_frame -= frames.size();
  }
  int i = current_frame;
  sprite.setTextureRect(frames[i]);
  if (flip) {
    sprite.setTextureRect(frames_flip[i]);
  }
}

void Animation::setFlip(bool value) {
  flip = value;
}

void Animation::setSpritePosition(int x, int y) {
  sprite.setPosition(x,y);
}
sf::Sprite Animation::getSprite() {
  return sprite;
}

void Animation::setPlay(bool value) {
  is_playing = value;
}

float Animation::getCurrentFrame() {
  return current_frame;
}

std::vector<sf::IntRect> Animation::getFrames() {
  return frames;
}