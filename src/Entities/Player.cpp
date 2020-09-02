#include "Player.h"
#include "ResourcePath.hpp"

Player::Player(const sf::Rect<float> &position, int hp, int dmg, int points, const std::vector<int> &armorLvl)
    : Entity(position.left, position.top, 0, 0, 64, 64),
      startPlayerPosition(position),
      hp(hp),
      dmg(dmg),
      arm(0),
      points(points),
      state(STAY),
      dir(false),
      finish(false),
      isFinishPosition(false),
      isGetVaccine(false),
      damagedAnimTimer(0),
      treatAnimTimer(0),
      fireAnimTimer(0),
      winAnimTimer(0),
      jumpTimer(0),
      hitTimer(0) {
  anim = AnimationManager(resourcePath() + "files/images/doctor.png");

  anim.Create("stay", 4, 4, 64, 64, 8, 0.0005, 72);
  anim.Create("walk", 76, 76, 64, 64, 7, 0.005, 72);
  anim.Create("fire", 4, 147, 64, 64, 3, 0.007, 72);
  anim.Create("die", 4, 219, 64, 64, 4, 0.004, 72);
  anim.Create("jump", 4, 295, 64, 64, 7, 0.007, 72);
  anim.Create("lay", 152, 362, 64, 64, 1, 0.000, 0);
  anim.Create("damaged", 4, 435, 64, 64, 2, 0.004, 72);
  anim.Create("lay_walk", 4, 507, 64, 64, 6, 0.005, 72);
  //anim.Create("lay_fire", 0, 744, 33, 76, 4, 0.0045, 38);
  anim.Create("treat", 4, 651, 64, 64, 5, 0.002, 72);
  //anim.Create("jump_fire", 0, 744, 33, 76, 4, 0.0045, 38);
  //anim.Create("drive", 0, 744, 33, 76, 4, 0.0045, 38);

  armors.push_back(Shoes(position.left, position.top, 64, 64, armorLvl[0]));
  armors.push_back(Cap(position.left, position.top, 64, 64, armorLvl[1]));
  armors.push_back(Robe(position.left, position.top, 64, 64, armorLvl[2]));

  for (auto &i : armors) {
    arm += i.GetArm();
  }
}

//void Player::checkAction() {
//    if (action[NO_KEY_PRESSED]) {
//
//    } else {
//        if (action[RIGHT_KEY_PRESSED]) {
//        }
//
//        if (action[LEFT_KEY_PRESSED]) {
//        }
//
//        if (action[UP_KEY_PRESSED]) {
//        }
//
//        if (action[DOWN_KEY_PRESSED]) {
//        }
//
//        if (action[DRIVE_KEY_PRESSED]) {
//        }
//
//        if (action[FIRE_KEY_PRESSED]) {
//        }
//    }
//
//
//
//    if (action[LEFT_KEY_PRESSED]) {
//        dir = true;
//        if (state == STAY || state == JUMP) {
//            state = WALK;
//            dx = -0.13;
//            treat = false;
//        }
//    }
//
//    if (action[RIGHT_KEY_PRESSED]) {
//        dir = false;
//        if (state == STAY || state == JUMP) {
//            state = WALK;
//            dx = 0.13;
//            treat = false;
//        }
//    }
//
//    if (action[UP_KEY_PRESSED]) {
//        if (state == STAY || state == WALK) {
//            dy = -0.2;
//            state = JUMP;
//            treat = false;
//        }
//    }
//
//    if (action[DOWN_KEY_PRESSED]) {
//        if (state != JUMP) {
//            if (state == WALK) {
//                state = LAY_WALK;
//            } else {
//                state = LAY;
//            }
//            treat = false;
//        }
//    }
//
//    if (!(action[LEFT_KEY_PRESSED] || action[RIGHT_KEY_PRESSED])) {
//        dx = 0;
//        if (state == WALK) {
//            state = STAY;
//        }
//    }
//
//    if (!action[UP_KEY_PRESSED]) {
//        if (state == JUMP) {
//            dy = 0.2;
//        }
//    }
//
//    if (action[FIRE_KEY_PRESSED]) {
//        fireTimer = 20;
//        fire = true;
//    }
//
//
//    for (std::map<ACTION, bool>::iterator it = action.begin(); it != action.end(); ++it) {
//        it->second = false;
//    }
//    action[NO_KEY_PRESSED] = true;
//}

void Player::Update(float time, std::vector<Object> &obj) {
}

//void Player::Update(float time, std::vector<Object> &obj) {
//    dx = 0;
//    dy = 0;
//    dir = false;
//
//    setDir(dir);
//
//
//
//
//
//
//
//    checkAction();
//
//    if (state == STAY) {
//        setAnim("stay");
//    }
//
//    if (state == WALK) {
//        setAnim("walk");
//    }
//
//    if (state == JUMP) {
//        setAnim("jump");
//    }
//
//    if (state == LAY) {
//        setAnim("lay");
//    }
//
//    if (state == LAY_WALK) {
//        setAnim("lay_walk");
//    }
//
//    if (hp > 0) {
//        rect.left += dx * time;
//    }
//
//    if (tookDmg) {
//        setAnim("damaged");
//        --damagedTimer;
//
//        if (damagedTimer == 0) {
//            tookDmg = false;
//        }
//    }
//
//    collision(0, obj);
//
//    if (fire) {
//        setAnim("fire");
//        --fireTimer;
//        if (fireTimer == 0) {
//            fire = false;
//        }
//    }
//
//    setDir(dir);
//
//    if (state != JUMP) {
//        if ((state == STAY || state == WALK || state == LAY) && !isGround) {
//            setAnim("jump");
//        }
//
//        dy = 0.2;
//    }
//
//    if (state == JUMP) {
//        jumpTimer += 0.2 * time;
//        if (jumpTimer > 300) {
//            dy = 0.2;
//        }
//    }
//
//    rect.top += dy * time;
//    isGround = false;
//    collision(1, obj);
//
//    if (hp <= 0) {
//        setAnim("die");
//    }
//
//    if (treat && !alive) {
//        if (playFinishMusic == 2) {
//            playFinishMusic = 3;
//        }
//
//        if (playFinishMusic == 1) {
//            playFinishMusic = 2;
//        }
//
//        setAnim("treat");
//        --treatTimer;
//        if (treatTimer <= 0) {
//            alive = true;
//            treat = false;
//        }
//    }
//
//    anim.Tick(time);
//    obj[0].rect = rect;
//    bathrobe.Update(time, obj);
//    shoes.Update(time, obj);
//    cap.Update(time, obj);
//}

void Player::setAnim(const std::string &str) {
  anim.Set(str);

  for (auto &i : armors) {
    i.SetAnim(str);
  }
}

void Player::setDir(bool dir) {
  anim.Flip(dir);

  for (auto &i : armors) {
    i.FlipAnim(dir);
  }
}

//void Player::collision(int num, std::vector<Object> &objs) {
//    for (auto &obj : objs) {
//        if (rect.intersects(obj.rect)) {
//            if (obj.name == "wall") {
//                if (dy > 0 && num == 1) {
//                    rect.top = obj.rect.top - rect.height;
//                    dy = 0;
//                    isGround = true;
//                    if (state == JUMP) {
//                        maxJump = 0;
//                    }
//                    state = STAY;
//                }
//
//                if (dy < 0 && num == 1) {
//                    rect.top = obj.rect.top + obj.rect.height;
//                    dy = 0;
//                    maxJump = 300;
//                }
//
//                if (dx > 0 && num == 0) {
//                    rect.left = obj.rect.left - rect.width;
//                }
//
//                if (dx < 0 && num == 0) {
//                    rect.left = obj.rect.left + obj.rect.width;
//                }
//            }
//
//            if (obj.name == "death" && obj.rect.intersects(rect)) {
//                rect.left = startPlayerPosition.rect.left;
//                rect.top = startPlayerPosition.rect.top;
//            }
//
//            finish = false;
//            isFinishPosition = false;
//            if (obj.name == "finish") {
//                isFinishPosition = true;
//                if (isGetVaccine && !treat) {
//                    playFinishMusic = 1;
//                    treat = true;
//                    treatTimer = 200;
//                }
//            }
//        }
//    }
//
//    if (!isFinishPosition) {
//        playFinishMusic = 0;
//    }
//}

void Player::Draw(sf::RenderWindow &window) {
  Draw(window);

  for (auto &i : armors) {
    i.Draw(window);
  }
}

void Player::SetAction(ACTION actionName) {
  action[actionName] = true;
  action[NO_KEY_PRESSED] = false;
}

void Player::GoToStart() {
  rect = startPlayerPosition;
}

void Player::SetPosition(float x, float y) {
  rect.left = x;
  rect.top = y;
}

std::vector<int> Player::GetMainData() {
  std::vector<int> data;
  data.push_back(hp);
  data.push_back(points);
  data.push_back(arm);
  data.push_back(armors[0].Getlvl());
  data.push_back(armors[1].Getlvl());
  data.push_back(armors[2].Getlvl());
  data.push_back(isGetVaccine);

  return data;
}

int Player::GetHp() const {
  return hp;
}

int Player::GetArm() const {
  return arm;
}

int Player::GetDmg() const {
  return dmg;
}

void Player::TakeDamge(int getDmg) {
  if (arm >= getDmg) {
    --hp;
  } else {
    hp += arm - getDmg;
  }

//    state = DAMAGED;
//    damagedAnimTimer = PLAYER_DAMAGED_ANIM_TIME;
}

int Player::GetPoints() const {
  return points;
}

void Player::ChangePoints(int getPoints) {
  points += getPoints;
}

bool Player::IsGetVaccine() const {
  return isGetVaccine;
}

void Player::SetVaccine(bool value) {
  isGetVaccine = value;
}

bool Player::GetDir() const {
  return dir;
}

bool Player::IsWin() const {
//    if (state == WIN) {
//        return true;
//    } else {
//        return false;
//    }
}

bool Player::IsFinishPosition() const {
  return isFinishPosition;
}

int Player::GetFinishTimer() const {
//    if (state == TREAT) {
//        return PLAYER_TREAT_ANIM_TIME - treatAnimTimer;
//    }
//
//    if (state == WIN) {
//        return PLAYER_TREAT_ANIM_TIME + PLAYER_WIN_ANIM_TIME - winAnimTimer;
//    }

  return -1;
}

float Player::GetHitTimer() const {
  return hitTimer;
}

void Player::ResetHitTimer() {
  hitTimer = 0;
}
