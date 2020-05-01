#include "Animation.h"

Animation::Animation(sf::Texture &t, int x, int y, int w, int h, int count, float speed, int step) {
  this->speed = speed;
  sprite.setTexture(t);
  sprite.setOrigin(0, h);
  currentFrame = 0;
  isPlaying = true;
  flip = false;
  for (int kI = 0; kI < count; ++kI) {
    frames.emplace_back(x + kI * step, y, w, h);
    framesFlip.emplace_back(x + kI * step + w, y, -w, h);
  }
}

void Animation::Tick(float time) {
  if (!isPlaying) {
    return;
  }
  currentFrame += speed * time;
  if (currentFrame > frames.size()) {
    currentFrame -= frames.size();
  }
  int i = currentFrame;
  sprite.setTextureRect(frames[i]);
  if (flip) {
    sprite.setTextureRect(framesFlip[i]);
  }
}

void Animation::SetFlip(bool value) {
  flip = value;
}

void Animation::SetSpritePosition(int x, int y) {
  sprite.setPosition(x, y);
}
sf::Sprite Animation::GetSprite() {
  return sprite;
}

void Animation::SetPlay(bool value) {
  isPlaying = value;
}

float Animation::GetCurrentFrame() const {
  return currentFrame;
}

std::vector<sf::IntRect> Animation::GetFrames() {
  return frames;
}