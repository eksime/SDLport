#include "Shark.h"
#include "Player.h"

Shark::Shark(Coords c) : Entity(c) {
  setTexture("shark");
  entType = SHARK;
  health = 1;
  maxHealth = 1;
  invincible = false;
  collisionRadius = 16;
}
void Shark::move() {
  Coords distance;
  float diagDistance;

  distance = player->coords - coords;
  diagDistance = distance.pyth();

  if (fabsf(distance.x) > fabsf(distance.y)) {
    movement.x = distance.x > 0 ? 1 : -1;
    movement.y = distance.y / fabsf(distance.x);
  } else {
    movement.y = distance.y > 0 ? 1 : -1;
    movement.x = distance.x / fabsf(distance.y);
  }

  if (diagDistance<300) {
    movement.x *= 2;
    movement.y *= 2;
    invincible = false;
  } else {
    invincible = true;
  }

  coords = coords + movement;
}

Shark::~Shark() {};