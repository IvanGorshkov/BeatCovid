#pragma once

#include "Entity.h"

class Transport : public Entity {
 public:
  explicit Transport(float x, float y, int height, int weight);
  void SetDrive();
  bool IsDrive() const;
  bool GetDir() const;
 protected:
  bool dir;
  bool isDrive;
  bool isHitWall;
};
