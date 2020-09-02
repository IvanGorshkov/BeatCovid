#pragma once

#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Armor.h"
#include "Robe.h"
#include "Shoes.h"
#include "Cap.h"

#define PLAYER_DX 0.13
#define PLAYER_DY 0.13
#define PLAYER_MAX_JUMP_TIME 300
#define PLAYER_HIT_TIME 1000
#define PLAYER_FIRE_ANIM_TIME 20
#define PLAYER_TREAT_ANIM_TIME 200
#define PLAYER_WIN_ANIM_TIME 100
#define PLAYER_DAMAGED_ANIM_TIME 30

enum ACTION {
    NO_KEY_PRESSED,
    DOWN_KEY_PRESSED,
    UP_KEY_PRESSED,
    LEFT_KEY_PRESSED,
    RIGHT_KEY_PRESSED,
    DRIVE_KEY_PRESSED,
    FIRE_KEY_PRESSED
};

class Player : public Entity {
public:
    explicit Player(const sf::Rect<float> &position, int hp, int dmg, int points, const std::vector<int> &armorLvl);
    void Update(float time, std::vector<Object> &obj) override;
    void SetAction(ACTION actionName);
    void SetPosition(float x, float y);
    void GoToStart();
    void Draw(sf::RenderWindow &window);
    std::vector<int> GetMainData();
    
    
    int GetHp() const;
    int GetArm() const;
    int GetDmg() const;
    void TakeDamge(int getDmg);
    int GetPoints() const;
    void ChangePoints(int getPoints);
    bool IsGetVaccine() const;
    void SetVaccine(bool value = true);
    bool GetDir() const;
    
    bool IsWin() const;
    bool IsFinishPosition() const;
    
    int GetFinishTimer() const;
    float GetHitTimer() const;
    void ResetHitTimer();
    
private:
    enum STATE {
        STAY,
        WALK,
//        CROUCH,
//        CHROUCH_WALK
    } state;
    
    void checkAction();
    void collision(std::vector<Object> &objs);
    void setAnim(const std::string &str);
    void setDir(bool dir);
    
    
    
    
    int hp;
    int arm;
    int dmg;
    int points;
    bool isGetVaccine;
    bool dir;
    
    int damagedAnimTimer;
    int fireAnimTimer;
    int treatAnimTimer;
    int winAnimTimer;
    int dieAnimTimer;
    
    
    float jumpTimer;
    float hitTimer;
    
    bool isFinishPosition;
    bool finish;
    
    std::map<ACTION, bool> action;
    sf::FloatRect startPlayerPosition;
    
    std::vector<Armor> armors;
};
