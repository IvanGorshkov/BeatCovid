#include "GameFPS.h"

GameFPS::GameFPS()
    : mFrame(0),
      mFps(0) {
}

unsigned int GameFPS::GetFPS() const {
  return mFps;
}

void GameFPS::Update() {
  if (mClock.getElapsedTime().asSeconds() >= 1.f) {
    mFps = mFrame;
    mFrame = 0;
    mClock.restart();
  }

  mFrame++;
}
