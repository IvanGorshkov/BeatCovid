//
// Created by Ivan Gorshkov on 25.04.2020.
//

#include "Player.h"
#include <iostream>

Player::Player(Object position)
    : arm(100), hp(100), dx(0.1), max_jump(0), STATE(STAY), isGround(true) {
  sf::Texture player_t;
  player_t.loadFromFile("../fang.png");
  anim = AnimationManager(player_t);

  anim.create("walk", 0, 244, 40, 50, 6, 0.005, 40);
  anim.create("stay", 0, 187, 42, 52, 3, 0.002, 42);
  anim.create("die", 0, 1199, 59, 41, 7, 0.004, 59);
  anim.create("jump", 0, 528, 29, 30, 4, 0.0045, 38);
  anim.create("lay", 0, 436, 80, 20, 1, 0);
  rect = sf::FloatRect(position.rect.left, position.rect.top, 40, 50);
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

void Player::status(float time, std::vector<Object> objs) {
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

  collision(0, objs);
  if (STATE != JUMP) {
    if ((STATE == STAY || STATE == RUN || STATE == LAY) && isGround == false) {
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
  isGround = false;

  collision(1, objs);

  if (hp <= 0) {
    anim.set("die");
    if (anim.getCurrentFrame() == 6) {
      anim.pause();
    }
  }

  anim.tick(time);
}

void Player::collision(int num, std::vector<Object> objs) {
  for (int i = 0; i < objs.size(); i++) {
    if (rect.intersects(objs[i].rect)) {
      if (objs[i].name == "wall") {
        if (dy > 0 && num == 1) {
          rect.top = objs[i].rect.top - rect.height;
          dy = 0;
          isGround = true;
          if (STATE == JUMP) {
            max_jump = 0;
          }
          STATE = STAY;
          return;
        }

        if (dy < 0 && num == 1) {
          rect.top = objs[i].rect.top + objs[i].rect.height;
          dy = 0;
          max_jump = 200;
          return;
        }

        if (dx > 0 && num == 0) {
          rect.left = objs[i].rect.left - rect.width;
          return;
        }

        if (dx < 0 && num == 0) {
          rect.left = objs[i].rect.left + objs[i].rect.width;
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
  anim.draw(window, rect.left, rect.top + rect.height);
}

void Player::setKey(std::string name, bool value) {
  key[name] = value;
}
