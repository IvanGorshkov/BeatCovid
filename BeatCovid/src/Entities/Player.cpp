#include "Player.h"
#include "ResourcePath.hpp"

Player::Player(const Object &position, std::vector<int> armors, float hp, int dmg, int points)
    : Entity(position.rect.left, position.rect.top, 0.1, 0.1, 64, 64),
      hp(hp),
      max_jump(0),
      arm(0),
      STATE(STAY),
      isGround(true),
      points(points),
      vaccine(false),
      dmg(dmg),
      fireC(0),
      isDrive(false),
      finish(false),
      tookDmg(false),
      fire(false),
      treat(false),
      alive(false),
      playFinishMusic(0),
      startPlayerPosition(position),
      bathrobe(position.rect.left, position.rect.top, 64, 64, armors[2]),
      shoes(position.rect.left, position.rect.top, 64, 64, armors[1]),
      cap(position.rect.left, position.rect.top, 64, 64, armors[0]) {

  sf::Texture player_t;
  player_t.loadFromFile(resourcePath() +  "files/images/doctor.png");
  anim = AnimationManager(player_t);
  anim.Create("walk", 76, 76, 64, 64, 7, 0.005, 72);
  anim.Create("stay", 4, 4, 64, 64, 8, 0.0005, 72);
  anim.Create("jump", 4, 295, 64, 64, 7, 0.007, 72);
  anim.Create("lay", 152, 362, 64, 64, 1, 0.000, 0);
  anim.Create("walklay", 4, 507, 64, 64, 6, 0.005, 72);
  anim.Create("dmg", 4, 435, 64, 64, 2, 0.004, 72);
  anim.Create("fire", 4, 147, 64, 64, 3, 0.007, 72);
  anim.Create("die", 4, 219, 64, 64, 4, 0.004, 72);
  anim.Create("win", 0, 744, 33, 76, 4, 0.0045, 38);
  anim.Create("treat", 4, 651, 64, 64, 5, 0.002, 72);

  arm = bathrobe.GetArm() + shoes.GetArm() + cap.GetArm();
}

void Player::KeyCheck() {
  if (key["L"]) {
    dir = true;
    if (STATE == STAY) {
      STATE = RUN;
      dx = -0.13;
      treat = false;
    }
  }

  if (key["R"]) {
    dir = false;
    if (STATE == STAY) {
      STATE = RUN;
      dx = 0.13;
      treat = false;
    }
  }

  if (hp > 0) {
    if (key["UP"]) {
      if (STATE == STAY || STATE == RUN) {
        dy = -0.2;
        STATE = JUMP;
        treat = false;
      }
    }
  }

  if (key["DOWN"]) {
    if (STATE != JUMP) {
      if (STATE == RUN) {
        STATE = WALKLAY;
      } else {
        STATE = LAY;
      }
      treat = false;
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

  if (key["SPACE"]) {
    fireC = 20;
    fire = true;
  }

  key["R"] = key["L"] = key["UP"] = key["DOWN"] = key["SPACE"] = false;
}

int Player::GetDmg() const {
  return dmg;
}

void Player::Update(float time, std::vector<Object> &obj) {
  KeyCheck();
  if (STATE == STAY) {
    anim.Set("stay");
    bathrobe.SetAnim("stay");
    shoes.SetAnim("stay");
    cap.SetAnim("stay");
  }

  if (STATE == RUN) {
    anim.Set("walk");
    bathrobe.SetAnim("walk");
    shoes.SetAnim("walk");
    cap.SetAnim("walk");
  }

  if (STATE == JUMP) {
    anim.Set("jump");
    bathrobe.SetAnim("jump");
    shoes.SetAnim("jump");
    cap.SetAnim("jump");
  }

  if (STATE == LAY) {
    anim.Set("lay");
    bathrobe.SetAnim("lay");
    shoes.SetAnim("lay");
    cap.SetAnim("lay");
  }

  if (STATE == WALKLAY) {
    anim.Set("walklay");
    bathrobe.SetAnim("walklay");
    shoes.SetAnim("walklay");
    cap.SetAnim("walklay");
  }

  if (hp > 0) {
    rect.left += dx * time;
  }

  if (tookDmg) {
    anim.Set("dmg");
    bathrobe.SetAnim("dmg");
    shoes.SetAnim("dmg");
    cap.SetAnim("dmg");
    --dmgC;

    if (dmgC == 0) {
      tookDmg = false;
    }
  }

  Collision(0, obj);

  if (fire) {
    anim.Set("fire");
    bathrobe.SetAnim("fire");
    shoes.SetAnim("fire");
    cap.SetAnim("fire");
    --fireC;
    if (fireC == 0) {
      fire = false;
    }
  }
  anim.Flip(dir);
  bathrobe.FlipAnim(dir);
  shoes.FlipAnim(dir);
  cap.FlipAnim(dir);

  if (STATE != JUMP) {
    if ((STATE == STAY || STATE == RUN || STATE == LAY) && !isGround) {
      anim.Set("jump");
      bathrobe.SetAnim("jump");
      shoes.SetAnim("jump");
      cap.SetAnim("jump");
    }
    dy = 0.2;
  }

  if (STATE == JUMP) {
      max_jump += 0.2*time;
    if (max_jump > 300) {
      dy = 0.2;
    }
  }

  rect.top += dy * time;
  isGround = false;
  Collision(1, obj);

  if (hp <= 0) {
    anim.Set("die");
    bathrobe.SetAnim("die");
    shoes.SetAnim("die");
    cap.SetAnim("die");
    if (anim.GetCurrentFrame() == 3) {
      anim.Pause();
      bathrobe.StatusAnim();
      shoes.StatusAnim();
      cap.StatusAnim();
    }
  }

  if (treat && !alive) {
    if (playFinishMusic == 2) {
      playFinishMusic = 3;
    }

    if (playFinishMusic == 1) {
      playFinishMusic = 2;
    }

    anim.Set("treat");
    bathrobe.SetAnim("treat");
    shoes.SetAnim("treat");
    cap.SetAnim("treat");
    --treatC;
    if (treatC <= 0) {
      alive = true;
      treat = false;
    }
  }

  anim.Tick(time);
  obj[0].rect = rect;
  bathrobe.Update(time, obj);
  shoes.Update(time, obj);
  cap.Update(time, obj);
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
          max_jump = 300;
        }

        if (dx > 0 && num == 0) {
          rect.left = obj.rect.left - rect.width;
        }

        if (dx < 0 && num == 0) {
          rect.left = obj.rect.left + obj.rect.width;
        }
      }

      if (obj.name == "death" && obj.rect.intersects(rect)) {
        rect.left = startPlayerPosition.rect.left;
        rect.top = startPlayerPosition.rect.top;
      }

      finish = false;
      isFinishPosition = false;
      if (obj.name == "finish") {
        isFinishPosition = true;
        if (vaccine && !treat) {
          playFinishMusic = 1;
          treat = true;
          treatC = 200;
        }
      }
    }
  }

  if (!isFinishPosition) {
    playFinishMusic = 0;
  }
}

void Player::DrawObjs(sf::RenderWindow &window) {
  Draw(window);
  bathrobe.Draw(window);
  shoes.Draw(window);
  cap.Draw(window);
}

float Player::TakeDamge(float getDmg) {
  if (getDmg == 0) {
    return hp;
  }

  if (hp > 0) {
    if (GetArm() >= getDmg) {
      --hp;
    } else {
      hp += GetArm() - getDmg;
    }
    dmgC = 30;
    tookDmg = true;
  }
  return hp;
}

float Player::GetHp() const {
  return hp;
}

float Player::GetArm() const {
  return bathrobe.GetArm() + shoes.GetArm() + cap.GetArm();
}

bool Player::GetDir() const {
  return dir;
}

void Player::SetKey(const std::string &name, bool value) {
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

void Player::GoToStart() {
  rect.left = startPlayerPosition.rect.left;
  rect.top = startPlayerPosition.rect.top;
}

void Player::ChangeHP(float getHp) {
  this->hp = getHp;
}

void Player::ChangeARM(float getArm) {
  this->arm = getArm;
}

AnimationManager Player::GetAnim() {
  return anim;
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
  data.push_back(shoes.Getlvl());
  data.push_back(cap.Getlvl());
  data.push_back(bathrobe.Getlvl());
  data.push_back(vaccine);

  return data;
}

Robe Player::GetRobe() {
  return bathrobe;
}

Cap Player::GetCap() {
  return cap;
}

Shoes Player::GetShoes() {
  return shoes;
}

void Player::SetDrive() {
  isDrive = !isDrive;
}

bool Player::IsDrive() const {
  return isDrive;
}

bool Player::IsFinishPosition() const {
  if (treat || alive) {
    return false;
  }

  return isFinishPosition;
}

bool Player::GetAlive() const {
  return alive;
}
void Player::SetFinish(bool getFinish) {
  this->finish = getFinish;
}

bool Player::GetTreat() const {
  return treat;
}

int Player::PlayFinishMusic() const {
  return playFinishMusic;
}
