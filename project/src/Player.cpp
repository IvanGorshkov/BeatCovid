//
// Created by Ivan Gorshkov on 25.04.2020.
//

#include "Player.h"
#include <iostream>

Player::Player(AnimationManager &a_m, Level &lev)
              : obj(lev.GetAllObjects())
              , arm(100)
              , hp(100)
              , dx(0.1)
              , max_jump(0)
              , anim(a_m)
              , STATE(STAY)
              , isGround(true) {
  Object pl = lev.GetObject("player");
   rect = sf::FloatRect(pl.rect.left, pl.rect.top ,40,50);
}

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
        dy = -0.2;
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
      dy = 0.2;
    }
  }

  key["R"] = key["L"] = key["UP"] = key["DOWN"] = false;
}

sf::FloatRect Player::getRect() {
  return rect;
}

void Player::status(float time) {
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

  collision(0);
  if (STATE != JUMP) {
    if ((STATE == STAY || STATE == RUN ||  STATE == LAY) && isGround == false) {
      anim.set("jump");
    }
    dy = 0.2;
  }

  if (STATE == JUMP) {
    max_jump += 0.2;
    if (max_jump > 150) {
      dy = 0.2;
    }
  }

  rect.top += dy * time;
  isGround= false;

  collision(1);

  if (hp <= 0) {
    anim.set("die");
    if (anim.getCurrentFrame() == 6) {
      anim.pause();
    }
  }

  anim.tick(time);
}

void Player::collision (int num) {
  for (int i=0;i<obj.size();i++) {
    if (rect.intersects(obj[i].rect)) {
      if (obj[i].name=="wall") {
        if (dy>0 && num == 1) {
          rect.top = obj[i].rect.top -  rect.height;
          dy = 0;
          isGround = true;
          if (STATE == JUMP) {
            max_jump = 0;
          }
          STATE = STAY;
          return;
        }

        if (dy<0 && num == 1) {
          rect.top = obj[i].rect.top + obj[i].rect.height;
          dy=0;
          max_jump = 200;
          return;
        }

        if (dx>0 && num == 0) {
          rect.left = obj[i].rect.left - rect.width;
          return;
        }

        if (dx<0 && num == 0) {
          rect.left = obj[i].rect.left + obj[i].rect.width;
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

void Player::draw(sf::RenderWindow &window) {
  anim.draw(window,rect.left,rect.top + rect.height);
}

void Player::setKey(std::string name, bool value) {
  key[name] = value;
}
