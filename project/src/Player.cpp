//
// Created by Ivan Gorshkov on 25.04.2020.
//

#include "Player.h"
#include <iostream>

Player::Player(Object position)
    : Entity(position.rect.left, position.rect.top, 0.1, 0.1, 50, 40),
      arm(100),
      hp(100),
      max_jump(0),
      STATE(STAY),
      isGround(true),
      points(0),
      vaccine(false),
      dmg(1) {
  sf::Texture player_t;
  player_t.loadFromFile("../files/images/fang.png");
  anim = AnimationManager(player_t);
  anim.create("walk", 0, 244, 40, 50, 6, 0.005, 40);
  anim.create("stay", 0, 187, 42, 52, 3, 0.002, 42);
  anim.create("die", 0, 1199, 59, 41, 7, 0.004, 59);
  anim.create("jump", 0, 528, 29, 30, 4, 0.0045, 38);
  anim.create("win", 0, 744, 33, 76, 4, 0.0045, 38);
  anim.create("lay", 0, 436, 80, 20, 1, 0);
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

int Player::GetDmg() {
  return dmg;
}

void Player::Update(float time, std::vector<Object> &obj) {
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

  collision(0, obj);
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

  collision(1, obj);

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

      if (objs[i].name == "finish" && vaccine == true) {
        anim.set("win");
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

bool Player::GetDir() {
  return dir;
}

void Player::setKey(std::string name, bool value) {
  key[name] = value;
}

void Player::AddPoints(int points) {
  this->points += points;
}

int Player::GetPoints() {
  return points;
}

bool Player::GetVaccine() {
  return vaccine;
}

void Player::SetVaccine(bool value) {
  vaccine = value;
}
