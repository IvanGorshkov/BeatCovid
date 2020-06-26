#pragma once

#include "Transport.h"

#define FUEL_LOSS 0.1
//#define AUTO_FUEL 50
#define AUTO_DX 0.3
//#define MONORAIL_FUEL 100
#define MONORAIL_DX 0.4

class SafeTransport : public Transport {
 public:
  explicit SafeTransport(float x, float y, int height, int weight, const std::string &name, std::vector<float> config);
  void Update(float time, std::vector<Object> &obj) override;
  float GetFuel() const;

 private:
  std::vector<float> config;
  float fuel;
  void setAuto();
  void setMonorail();
};
