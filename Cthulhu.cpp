#include "Cthulhu.h"
#include "player.h"

Cthulhu::Cthulhu(Coords c) : Entity(c) {
  setTexture("cthulhu");
  entType = CTHULHU;
  health = 100;
  maxHealth = 100;
  invincible = false;
  collisionRadius = 32;
}

void Cthulhu::move() {
  Coords distance;
  distance = player->coords - coords;

  if (fabsf(distance.x) > fabsf(distance.y)) {
    movement.x = distance.x > 0 ? 1 : -1;
    movement.y = distance.y / fabsf(distance.x);
  } else {
    movement.y = distance.y > 0 ? 1 : -1;
    movement.x = distance.x / fabsf(distance.y);
  }

  movement.x = movement.x * (3.5f - 3 * (health / 100.0f));
  movement.y = movement.y * (3.5f - 3 * (health / 100.0f));

  coords = coords + movement;
}

Cthulhu::~Cthulhu() {};