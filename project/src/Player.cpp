//
// Created by Ivan Gorshkov on 25.04.2020.
//

#include "Player.h"
#include <iostream>

Player::Player(sf::Texture &image) {
  sprite.setTexture(image);
  rect = sf::FloatRect(16,200,16,16);
  currentFrame = 0;
  isGround = true;
  isJump = true;
  dx = 0.1;
  jumphight = 0;
}

sf::Sprite Player::getSprite() {
  return sprite;
}

sf::FloatRect Player::getRect() {
  return rect;
}

void Player::jump() {
  if (isJump == true) {
    dy = -0.1;
    jumphight += 0.1;
    isGround = false;
    std::cout << jumphight << std::endl;
    if (jumphight > 20) {
      isJump = false;
    }
  }
}

void Player::move(float dx) {
  this->dx = dx;
  currentFrame += 0.03;
}

void Player::status(float offsetX, float offsetY, float time, std::string *TileMap) {
  rect.left += dx * time;
  collision(0, TileMap);
  if (isGround == false) {
    dy=dy + 0.0005 * time;
  }

  rect.top += dy * time;
  isGround= false;
  collision(1, TileMap);

  if (currentFrame > 5) {
    currentFrame -= 5;
  }

  if (this->dx > 0) {
    sprite.setTextureRect(sf::IntRect(112+31*int(currentFrame),144,16,16));
  }

  if (this->dx < 0) {
    sprite.setTextureRect(sf::IntRect(112+31*int(currentFrame)+16,144,-16,16));
  }

  sprite.setPosition(rect.left - offsetX, rect.top- offsetY);
  dx=0;
}

void Player::collision (int num, std::string *TileMap) {
  for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++) {
    for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++) {
      if ((TileMap[i][j]=='P') || (TileMap[i][j]=='k') || (TileMap[i][j]=='0') ||
      (TileMap[i][j]=='r') || (TileMap[i][j]=='t')) {
        if (dy>0 && num == 1) {
          rect.top = i * 16 -  rect.height;
          dy = 0;
          isGround = true;
          isJump = true;
          jumphight = 0;
          return;
        }

        if (dy<0 && num == 1) {
          rect.top = i*16 + 16;
          dy=0;
          return;
        }

        if (dx>0 && num == 0) {
          rect.left = j * 16 - rect.width;
          return;
        }

        if (dx<0 && num == 0) {
          rect.left = j * 16 + 16;
          return;
        }
      }
    }
  }
}
