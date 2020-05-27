#include "Transport.h"

Transport::Transport(float x, float y, int height, int weight)
    : Entity(x, y, 0, 0, height, weight),
      isDrive(false),
      isHitWall(false),
      dir(false) {
}

void Transport::SetDrive() {
  if (isDrive && isHitWall) {
    dir = !dir;
    isHitWall = false;
  }

  isDrive = !isDrive;
}

bool Transport::IsDrive() const {
  return isDrive;
}

bool Transport::GetDir() const {
  return dir;
}
