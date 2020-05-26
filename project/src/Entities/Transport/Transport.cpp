#include "Transport.h"

Transport::Transport(float x, float y, int height, int weight)
    : Entity(x, y, 0, 0, height, weight),
      isDrive(false),
      isHitWall(false) {
}

void Transport::SetDrive() {
  isDrive = !isDrive;
}

bool Transport::IsDrive() const {
  return isDrive;
}
