#include "Bullet.h"
#include "Mouse.h"
#include "Player.h"
#include "GameState.h"

Bullet::Bullet(Coords c, Coords t) : Entity(c) {
  setTexture("bullet");
  entType = BULLET;
  health = 1;
  damage = player->damage;
  maxHealth = 1;
  invincible = false;
  target = t;
  collisionRadius = 16;
}

void Bullet::move() {
  if (movement.x == 0 && movement.y == 0) {
    //std::cout <<"player coords: "<<player->coords.x << '\t' << player->coords.y << std::endl;
    Coords distance;
    float diagDistance;

    if (0 == 0/*pollController() == 0*/) {
      distance = target - coords;
    } else {
      //xDistance = GAMEPAD_RIGHT_X;
      //yDistance = GAMEPAD_RIGHT_Y;
    }
    //std::cout <<"mouse coords: "<<mouse.coords.x << '\t' << mouse.coords.y << std::endl;
    diagDistance = distance.pyth();

    if (fabsf(distance.x) > fabsf(distance.y)) {
      movement.x = distance.x > 0 ? 1 : -1;
      movement.y = distance.y / fabsf(distance.x);

    } else {
      movement.y = distance.y > 0 ? 1 : -1;
      movement.x = distance.x / fabsf(distance.y);
    }
    movement.x *= 10;
    movement.y *= 10;
  }

  coords = coords + movement;

  if (coords.x < 0 || coords.y < 0 || coords.x > SCREEN_WIDTH || coords.y > SCREEN_HEIGHT) {
    health = 0;
  }

}

void Bullet::collide(Entity* with) {
  if (with->entType != BULLET && with->entType != PLAYER)
    if (with->invincible == false) {
    health = 0;
    with->health -= damage;
    if (with->health <= 0 && gameState.gameMode == GAME_STANDARD)
      switch (with->entType) {
      case(ICEBERG) :
        gameState.score += with->maxHealth;
        break;
      case(SHARK) :
        gameState.score += 2;
        break;
      case(CTHULHU) :
        gameState.score += 300;
        break;
    }
    }
}

Bullet::~Bullet() {};