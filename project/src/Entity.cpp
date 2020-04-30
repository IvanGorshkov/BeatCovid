#include "Entity.h"

#include <utility>

Entity::Entity(float x, float y, float dx, float dy, int width, int height)
    : dx(dx), dy(dy), isLife(true) {
  rect = sf::FloatRect(x, y, width, height);
}

sf::FloatRect Entity::GetRect() {
  return rect;
}

void Entity::Draw(sf::RenderWindow &window) {
  anim.draw(window, rect.left, rect.top + rect.height);
}

void Entity::SetAnimation(AnimationManager getAnim, std::string firstAnim) {
  anim = std::move(getAnim);
  anim.set(std::move(firstAnim));
}

bool Entity::IsLife() const {
  return isLife;
}

void Entity::SetLife(bool getIsLife) {
  this->isLife = getIsLife;
}