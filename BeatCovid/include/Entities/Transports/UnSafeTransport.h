#pragma once

#include "Transport.h"

#define HP_TIME_LOSS 2000
#define BUS_DMG 4
#define BUS_DX 0.3
#define METRO_DMG 5
#define METRO_DX 0.4

class UnSafeTransport : public Transport {
 public:
  explicit UnSafeTransport(float x, float y, int height, int weight, const std::string &name);
  void Update(float time, std::vector<Object> &obj) override;
  float GetDmg();
  float PrintDmg() const;

 private:
  float dmg;
  float timerHit;
  void setBus();
  void setMetro();
};