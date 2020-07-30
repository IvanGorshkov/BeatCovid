#include "Entity.h"

Entity::Entity(float x, float y, float dx, float dy, int width, int height)
    : dx(dx),
      dy(dy),
      isLife(true),
      rect(x, y, width, height) {
}

sf::FloatRect Entity::GetRect() {
  return rect;
}

void Entity::Draw(sf::RenderWindow &window) {
  anim.Draw(window, rect.left, rect.top + rect.height);
}

bool Entity::IsLife() const {
  return isLife;
}
