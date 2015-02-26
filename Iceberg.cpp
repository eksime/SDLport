#include "Iceberg.h"
#include "GameState.h"

Iceberg::Iceberg(Coords c) : Entity(c) { init(c, 1); }
Iceberg::Iceberg(Coords c, int h) : Entity(c) { init(c, h); }
void Iceberg::init(Coords c, int h) {
  setTexture("iceberg");
  entType = ICEBERG;
  health = h;
  maxHealth = h;
  invincible = false;
  collisionRadius = 16;
}

void Iceberg::move() {
  if (movement.x == 0) {
    movement.x = ((float)(rand() % 100 + 1)) / 100;
    if (coords.x>(SCREEN_WIDTH / 2))
      movement.x = -movement.x;
  }

  if (movement.y == 0) {
    movement.y = ((float)(rand() % 100 + 1)) / 100;
    if (coords.y>(SCREEN_HEIGHT / 2))
      movement.y = -movement.y;
  }

  coords = coords + movement;
}

void Iceberg::collide(Entity* with) {
  if (with->entType == ICEBERG) {
    health += with->health;
    maxHealth += with->maxHealth;
    collisionRadius = 16 + maxHealth * 2.5;
    with->health = 0;
  }
};
Iceberg::~Iceberg() {};