#include "Entity.h"

Entity::Entity(float x, float y, float dx, float dy, int width, int height)
    : dx(dx), dy(dy), isLife(true), timerDie(0), isDie(false) {
  rect = sf::FloatRect(x, y, width, height);
}

sf::FloatRect Entity::GetRect() {
  return rect;
}

void Entity::Draw(sf::RenderWindow &window) {
  anim.Draw(window, rect.left, rect.top + rect.height);
}

bool Entity::IsDie() {
  if (timerDie > 300) {
    isDie = true;
  }

  return isDie;
}

bool Entity::IsLife() const {
  return isLife;
}