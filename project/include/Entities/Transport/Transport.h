#pragma once

#include "Entity.h"

class Transport : public Entity {
 public:
  explicit Transport(float x, float y, int height, int weight, std::string name);
  void SetDrive();
  bool IsDrive() const;
  bool GetDir() const;
  std::string GetName();

 protected:
  std::string name;
  bool dir;
  bool isDrive;
  bool isHitWall;
};
