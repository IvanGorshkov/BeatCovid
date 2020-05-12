#include "Player.h"
#include <iostream>

Player::Player(const Object &position)
    : Entity(position.rect.left, position.rect.top, 0.1, 0.1, 50, 40),
      hp(100),
      max_jump(0),
      STATE(STAY),
      isGround(true),
      points(0),
      vaccine(false),
      dmg(1),
      finish(false),
      bathrobe(position.rect.left, position.rect.top, 50, 40, 1),
      gloves(position.rect.left, position.rect.top, 50, 40, 1),
      glasses(position.rect.left, position.rect.top, 50, 40, 1),
      mask(position.rect.left, position.rect.top, 50, 40, 1) {
  sf::Texture player_t;
  player_t.loadFromFile("../files/images/fang.png");
  anim = AnimationManager(player_t);
  anim.Create("walk", 0, 244, 40, 50, 6, 0.005, 40);
  anim.Create("stay", 0, 187, 42, 52, 3, 0.002, 42);
  anim.Create("die", 0, 1199, 59, 41, 7, 0.004, 59);
  anim.Create("jump", 0, 528, 29, 30, 4, 0.0045, 38);
  anim.Create("win", 0, 744, 33, 76, 4, 0.0045, 38);
  anim.Create("lay", 0, 436, 80, 20, 1, 0);
  arm = bathrobe.GetArm() + glasses.GetArm() + gloves.GetArm() + mask.GetArm();
}

void Player::KeyCheck() {
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

int Player::GetDmg() const {
  return dmg;
}

void Player::Update(float time, std::vector<Object> &obj) {
  KeyCheck();

  if (STATE == STAY) {
    anim.Set("stay");
    bathrobe.SetAnim("stay");
    gloves.SetAnim("stay");
    glasses.SetAnim("stay");
    mask.SetAnim("stay");
  }

  if (STATE == RUN) {
    anim.Set("walk");
    bathrobe.SetAnim("walk");
    gloves.SetAnim("walk");
    glasses.SetAnim("walk");
    mask.SetAnim("walk");
  }

  if (STATE == JUMP) {
    anim.Set("jump");
    bathrobe.SetAnim("jump");
    gloves.SetAnim("jump");
    glasses.SetAnim("jump");
    mask.SetAnim("jump");
  }

  if (STATE == LAY) {
    anim.Set("lay");
    bathrobe.SetAnim("lay");
    gloves.SetAnim("lay");
    glasses.SetAnim("lay");
    mask.SetAnim("lay");
  }

  anim.Flip(dir);
  bathrobe.FlipAnim(dir);
  gloves.FlipAnim(dir);
  glasses.FlipAnim(dir);
  mask.FlipAnim(dir);

  if (hp > 0) {
    rect.left += dx * time;
  }

  Collision(0, obj);
  if (STATE != JUMP) {
    if ((STATE == STAY || STATE == RUN || STATE == LAY) && !isGround) {
      anim.Set("jump");
      bathrobe.SetAnim("jump");
      gloves.SetAnim("jump");
      glasses.SetAnim("jump");
      mask.SetAnim("jump");
    }
    dy = 0.2;
  }

  if (STATE == JUMP) {
    max_jump += 0.2;
    if (max_jump > 10) {
      dy = 0.2;
    }
  }

  rect.top += dy * time;
  isGround = false;

  Collision(1, obj);

  if (hp <= 0) {
    anim.Set("die");
    bathrobe.SetAnim("die");
    gloves.SetAnim("die");
    glasses.SetAnim("die");
    mask.SetAnim("die");
    if (anim.GetCurrentFrame() == 6) {
      anim.Pause();
      bathrobe.StatusAnim();
      gloves.StatusAnim();
      glasses.StatusAnim();
      mask.StatusAnim();
    }
  }

  anim.Tick(time);
  obj[0].rect = rect;
  bathrobe.Update(time, obj);
  gloves.Update(time, obj);
  glasses.Update(time, obj);
  mask.Update(time, obj);
}
bool Player::GetFinish() const {
  return finish;
}
void Player::Collision(int num, std::vector<Object> &objs) {
  for (auto &obj : objs) {
    if (rect.intersects(obj.rect)) {
      if (obj.name == "wall") {
        if (dy > 0 && num == 1) {
          rect.top = obj.rect.top - rect.height;
          dy = 0;
          isGround = true;
          if (STATE == JUMP) {
            max_jump = 0;
          }
          STATE = STAY;
        }

        if (dy < 0 && num == 1) {
          rect.top = obj.rect.top + obj.rect.height;
          dy = 0;
          max_jump = 200;
        }

        if (dx > 0 && num == 0) {
          rect.left = obj.rect.left - rect.width;
        }

        if (dx < 0 && num == 0) {
          rect.left = obj.rect.left + obj.rect.width;
        }
      }

      finish = false;
      if (obj.name == "finish" && vaccine) {
        anim.Set("win");
        bathrobe.SetAnim("win");
        gloves.SetAnim("win");
        glasses.SetAnim("win");
        mask.SetAnim("win");
        finish = true;
      }
    }
  }
}
void Player::DrawObjs(sf::RenderWindow &window) {
  Draw(window);
  bathrobe.Draw(window);
  gloves.Draw(window);
  glasses.Draw(window);
  mask.Draw(window);
}

float Player::TakeDamge(float getDmg) {
  if (hp > 0) {
    if (arm > getDmg) {
      --hp;
    } else {
      hp += arm - getDmg;
    }
  }
  return hp;
}

float Player::GetHp() const {
  return hp;
}

float Player::GetArm() const {
  return arm;
}

bool Player::GetDir() const {
  return dir;
}

void Player::SetKey(const std::string& name, bool value) {
  key[name] = value;
}

void Player::AddPoints(int getPoints) {
  this->points += getPoints;
}

int Player::GetPoints() const {
  return points;
}

void Player::PenaltyPoints(int penaltyPoints) {
  points -= penaltyPoints;
}

bool Player::GetVaccine() const {
  return vaccine;
}

void Player::SetVaccine(bool value) {
  vaccine = value;
}

void Player::GoToStart(const Object &position) {
  rect.left = position.rect.left;
  rect.top = position.rect.top;
}

AnimationManager Player::GetAnim() {
  return anim;
}
