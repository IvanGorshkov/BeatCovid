//
// Created by Ivan Gorshkov on 27.04.2020.
//
#pragma once

#include <string>
#include <map>
#include "Animation.h"

class AnimationMenager {
 public:
  AnimationMenager() = default;
  void create(std::string name, sf::Texture &texture, int x, int y, int w, int h, int count, float speed, int step=0);
  void draw(sf::RenderWindow &window,int x=0, int y=0);
  void set(std::string name);
  void flip(bool b=1);
  void tick(float time);
  void pause();
  int getCurrentFrame();
 private:
  std::map<sf::String, Animation> anim_list;
  sf::String current_anim;
};
