//
// Created by Ivan Gorshkov on 27.04.2020.
//

#include "AnimationMenager.h"

void AnimationMenager::create(std::string name, sf::Texture &texture, int x, int y, int w, int h, int count, float speed, int step) {
  anim_list[name] = Animation(texture,x,y,w,h,count,speed,step);
  current_anim = name;
}

void AnimationMenager::draw(sf::RenderWindow &window,int x, int y) {
  anim_list[current_anim].setSpritePosition(x,y);
  window.draw(anim_list[current_anim].getSprite());
}

void AnimationMenager::set(std::string name) {
  current_anim = name;
}

void AnimationMenager::flip(bool b) {
  anim_list[current_anim].setFlip(b);
}

void AnimationMenager::tick(float time)	 {
  anim_list[current_anim].tick(time);
}

void AnimationMenager::pause() {
  anim_list[current_anim].setPlay(false);
}

int AnimationMenager::getCurrentFrame() {
  return anim_list[current_anim].getCurrentFrame();
}