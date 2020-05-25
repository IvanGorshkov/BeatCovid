#pragma once

#include "Entity.h"

class Transport : public Entity {
 public:
  explicit Transport(float x, float y, int height, int weight);
  void SetDrive();
  bool IsDrive() const;
 protected:
  bool isDrive;
  bool isHitWall;
};
