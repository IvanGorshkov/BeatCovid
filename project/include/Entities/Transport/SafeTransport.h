#pragma once

#include "Transport.h"
#define FUEL_LOSS 0.1
#define AUTO_FUEL 10
#define AUTO_DX 0.3
#define MONORAIL_FUEL 20
#define MONORAIL_DX 0.4

class SafeTransport : public Transport {
 public:
  explicit SafeTransport(float x, float y, int height, int weight, const std::string& name);
  void Update(float time, std::vector<Object> &obj) override;
  float GetFuel();
 private:
  std::string name;
  float fuel{};
  void setAuto();
  void setMonorail();
};
