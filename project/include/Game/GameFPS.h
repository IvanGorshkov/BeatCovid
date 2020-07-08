#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class GameFPS {
 public:
  GameFPS();
  void Update();
  unsigned int GetFPS() const;

 private:
  unsigned int mFrame;
  unsigned int mFps;
  sf::Clock mClock;
};
