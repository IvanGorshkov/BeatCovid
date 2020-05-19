#pragma once

#include "Transport.h"
#define FUEL_LOSS 0.1
#define AUTO_FUEL 100
#define AUTO_DX 0.12
#define MONORAIL_FUEL 100
#define MONORAIL_DX 0.1

class SafeTransport : public Transport {
 public:
  explicit SafeTransport(float x, float y, int height, int weight, std::string name);
  void Update(float time, std::vector<Object> &obj) override;
  float GetFuel();
 private:
  std::string name;
  float fuel;
  void setAuto();
  void setMonorail();
};
