//
// Created by Ivan Gorshkov on 25.04.2020.
//

#include "Player.h"
#include <iostream>

Player::Player(AnimationMenager &a_m)
              : arm(100)
              , hp(100)
              , dx(0.1)
              , max_jump(0)
              , anim(a_m)
              , STATE(STAY)
              , rect(sf::FloatRect(150,100,40,50))
              , isGround(true) {}

void Player::keyCheck() {
  if (key["L"]) {
    dir = true;
    if (STATE == STAY) {
      STATE = RUN;
      dx = -0.1;
    }
  }

  if (key["R"]) {
    dir = false;
    if (STATE == STAY) {
      STATE = RUN;
      dx = 0.1;
    }
  }

  if (hp > 0) {
    if (key["UP"]) {
      if (STATE == STAY || STATE == RUN) {
        dy = -2;
        STATE = JUMP;
      }
    }
  }

  if (key["DOWN"]) {
    if (STATE != JUMP) {
      STATE = LAY;
    }
  }

  if (!(key["L"] || key["R"])) {
    dx = 0;
    if (STATE == RUN) {
      STATE = STAY;
    }
  }

  if (!key["UP"]) {
    if (STATE == JUMP) {
      dy = 2;
    }
  }

  key["R"]=key["L"]=key["UP"] = key["DOWN"] = false;
}

sf::FloatRect Player::getRect() {
  return rect;
}

void Player::status(float time, std::string *TileMap) {


  keyCheck();

  if (STATE == STAY) {
    anim.set("stay");
  }

  if (STATE == RUN) {
    anim.set("walk");
  }

  if (STATE == JUMP) {
    anim.set("jump");

  }

  if (STATE == LAY) {
    anim.set("lay");

  }

  anim.flip(dir);
  if (hp > 0) {
  rect.left += dx * time;
  }
  collision(0, TileMap);
  if (STATE != JUMP) {
    dy += 0.002 * time;
  }

  if (STATE == JUMP) {
    max_jump += 2;
    if (max_jump > 200) {
      dy = 2;
    }
  }

  rect.top += dy;
  isGround= false;

  collision(1, TileMap);

  if (hp <= 0) {
    anim.set("die");

    if (anim.getCurrentFrame() == 6) {
      anim.pause();
    }
  }

  anim.tick(time);
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
          if (STATE == JUMP) {
            max_jump = 0;
          }
          STATE = STAY;
          return;
        }

        if (dy<0 && num == 1) {
          rect.top = i * 16 + 16;
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

void Player::draw(sf::RenderWindow &window, float offsetX, float offsetY)
{
  anim.draw(window,rect.left - offsetX,rect.top + rect.height - offsetY);
}

void Player::setKey(std::string name, bool value) {
  key[name] = value;
}
