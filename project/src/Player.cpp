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
  if (isJump == true && hp >= 0) {
    dy = -0.2;
    jumphight += 0.2;
    isGround = false;
    std::cout << jumphight << std::endl;
    if (jumphight > 40) {
      isJump = false;
    }
  }
}

void Player::move(float dx) {
  if (hp >= 0) {
    this->dx = dx;
    currentFrame += 0.03;
  }
}

void Player::status(float offsetX, float offsetY, float time, std::string *TileMap) {
  if (hp <= 0) {
    sprite.setColor(sf::Color::Red);
  }

  rect.left += dx * time;
  collision(0, TileMap);
  if (isGround == false) {
    dy=dy + 0.0005 * time;
  }

  rect.top += dy * time;
  isGround= false;
  collision(1, TileMap);

  if (currentFrame > 2) {
    currentFrame -= 2;
  }

  if (this->dx > 0) {
    sprite.setTextureRect(sf::IntRect(128*int(currentFrame),0,128,128));
  }

  if (this->dx < 0) {
    sprite.setTextureRect(sf::IntRect(128*int(currentFrame)+128,0,-128,128));
  }

  sprite.setPosition(rect.left - offsetX, rect.top- offsetY);
  dx=0;
}

void Player::collision (int num, std::string *TileMap) {
  for (int i = rect.top/32 ; i<(rect.top+rect.height)/32; i++) {
    for (int j = rect.left/32; j<(rect.left+rect.width)/32; j++) {
      if ((TileMap[i][j]=='P') || (TileMap[i][j]=='k') || (TileMap[i][j]=='0') ||
      (TileMap[i][j]=='r') || (TileMap[i][j]=='t')) {
        if (dy>0 && num == 1) {
          rect.top = i * 32 -  rect.height;
          dy = 0;
          isGround = true;
          isJump = true;
          jumphight = 0;
          return;
        }

        if (dy<0 && num == 1) {
          rect.top = i*32 + 32;
          dy=0;
          isJump = false;
          return;
        }

        if (dx>0 && num == 0) {
          rect.left = j * 32 - rect.width;
          return;
        }

        if (dx<0 && num == 0) {
          rect.left = j * 32 + 32;
          return;
        }
      }
    }
  }
}

float Player::takeDamge(float dmg) {
  if (arm > 0) {
    arm -= dmg;
  } else {
    hp -= dmg;
  }
  return hp;
}

float Player::getHp() {
  return hp;
}

float Player::getArm() {
  return arm;
}
