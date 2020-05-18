#pragma once

#include "Transport.h"
#define HP_TIME_LOSS 2000
#define BUS_DMG 6
#define BUS_DX 0.12
#define METRO_DMG 7
#define METRO_DX 0.1

class UnSafeTransport : public Transport {
 public:
  explicit UnSafeTransport(float x, float y, int height, int weight, std::string name);
  void Update(float time, std::vector<Object> &obj) override;
  float GetDmg();
  float PrintDmg();
 private:
  std::string name;
  float dmg;
  float timerHit;
  void setBus();
  void setMetro();
};