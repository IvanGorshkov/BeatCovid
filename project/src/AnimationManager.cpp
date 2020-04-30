//
// Created by Ivan Gorshkov on 27.04.2020.
//

#include "AnimationManager.h"

AnimationManager::AnimationManager(sf::Texture &texture) : texture(texture) {}

void AnimationManager::create(std::string name, int x, int y, int w, int h, int count, float speed, int step) {
  anim_list[name] = Animation(texture, x, y, w, h, count, speed, step);
  current_anim = name;
}

void AnimationManager::draw(sf::RenderWindow &window, int x, int y) {
  anim_list[current_anim].setSpritePosition(x, y);
  window.draw(anim_list[current_anim].getSprite());
}

void AnimationManager::set(std::string name) {
  current_anim = name;
}

void AnimationManager::flip(bool b) {
  anim_list[current_anim].setFlip(b);
}

void AnimationManager::tick(float time) {
  anim_list[current_anim].tick(time);
}

void AnimationManager::pause() {
  anim_list[current_anim].setPlay(false);
}

int AnimationManager::getCurrentFrame() {
  return anim_list[current_anim].getCurrentFrame();
}
float AnimationManager::getH() {
  return anim_list[current_anim].getFrames()[0].height;
}

float AnimationManager::getW() {
  return anim_list[current_anim].getFrames()[0].width;
}
