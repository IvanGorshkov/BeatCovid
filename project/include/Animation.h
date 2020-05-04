#pragma once
#include <SFML/Graphics.hpp>

class Animation {
 public:
  Animation() = default;
  Animation(sf::Texture &t, int x, int y, int w, int h, int count, float speed, int step);
  void Tick(float time);
  void SetFlip(bool value);
  void SetPlay(bool value);
  float GetCurrentFrame() const;
  std::vector<sf::IntRect> GetFrames();
  void SetSpritePosition(int x, int y);
  sf::Sprite GetSprite();

 private:
  std::vector<sf::IntRect> frames;
  sf::Sprite sprite;
  bool flip;
  bool isPlaying;
  float speed;
  float currentFrame;
  std::vector<sf::IntRect> framesFlip;
};

