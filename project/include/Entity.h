#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationManager.h"

class Entity {
 public:
  explicit Entity(float x, float y, float dx, float dy, int height, int weight);
  sf::FloatRect GetRect();
  virtual void Update(float time);
  void Draw(sf::RenderWindow &window);
  void SetAnimation(AnimationManager getAnim, std::string firstAnim);
  bool IsLife() const;
  void SetLife(bool getIsLife);

 protected:
  bool isLife;
  float dx;
  float dy;
  sf::FloatRect rect;
  AnimationManager anim;
};