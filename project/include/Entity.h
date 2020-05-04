#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Level_map.h"
#include <list>

class Entity {
 public:
  Entity() = default;
  explicit Entity(float x, float y, float dx, float dy, int height, int weight);
  sf::FloatRect GetRect();
  virtual void Update(float time, std::vector<Object> &obj) = 0;
  void Draw(sf::RenderWindow &window);
  bool IsDie();
  bool IsLife() const;

 protected:
  bool isLife;
  bool isDie;
  float timerDie;
  float dx;
  float dy;
  sf::FloatRect rect;
  AnimationManager anim;
};