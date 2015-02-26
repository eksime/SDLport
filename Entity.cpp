#include "Entity.h"
#include "GameState.h"
#include "Mouse.h"
#include "Input.h"

std::list<Entity*> Entity::entities;

bool Entity::setTexture(std::string t) {
  if (!LTexture::texturePool.count(t))
    return false;

  texture = &LTexture::texturePool[t];
  return true;
}

void Entity::render() {
  if (texture)
    texture->render(coords.x - (texture->getWidth() / 2), coords.y - (texture->getHeight() / 2), NULL, atan2f(movement.y, movement.x) * 57.2957795f);
}

Entity::Entity(Coords c) {
  texture = (LTexture*)(0);
  coords = c;
}

bool Entity::collisionCheck(Entity* e) {
  return (coords - e->coords).pyth() <= (collisionRadius + e->collisionRadius);
}
Entity::~Entity() {}

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

Bullet::Bullet(Coords c, Coords d) : Entity(c) {
  setTexture("bullet");
  entType = BULLET;
  health = 1;
  damage = player->damage;
  maxHealth = 1;
  invincible = false;
  collisionRadius = 16;
}

void Bullet::move() {
  if (movement.x == 0 && movement.y == 0) {
    //std::cout <<"player coords: "<<player->coords.x << '\t' << player->coords.y << std::endl;
    Coords distance;
    float diagDistance;

    if (0==0/*pollController() == 0*/) {
      distance = mouse.coords - player->coords;
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
    with->health-= damage;
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
};

Bullet::~Bullet() {};

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
  float diagDistance;

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

Player::Player(Coords c, int h) : Entity(c) {
  setTexture("player");
  entType = PLAYER;
  name = "Player";
  speedmod = 1;
  health = h;
  maxHealth = h;
  invincible = false;
  collisionRadius = 16;
  playerInvuln = 0;
  damage = 1;
  entities.emplace_back(this);
  player = (Player*)entities.back();
}

void Player::collide(Entity* with) {
  if (with->entType == UPGRADE) {
    damage++;
  } else if (with->entType == SHIELD) {
    invincible = true;
    playerInvuln = 300;
  } else {
    switch (gameState.gameMode) {
    case GAME_STANDARD:
      if (invincible != true) {
        health--;
        coords = Coords(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        invincible = true;
        playerInvuln = 100;
      }
      break;
    case GAME_SURVIVAL:
      health = 0;
      break;
    case GAME_TITANIC:
      health += 2;	//health is timer in this mode so increase timer
      gameState.score += 2;
      break;
    }
  }
  with->health = 0;
  //respawn function. needs to call collision of the with entity
};

void Player::move() {
  /*
  float rx = GAMEPAD_LEFT_X, ry = GAMEPAD_LEFT_Y;
  e->movement.x = (rx == 0 ? (keys['a'] ? -1 : (keys['d'] ? 1 : 0)) : rx) * playerMoveSpeedModifier;	//if a, left. if d, right. else 0
  e->movement.y = (ry == 0 ? (keys['w'] ? -1 : (keys['s'] ? 1 : 0)) : ry) * playerMoveSpeedModifier;	//if w, up. if s, down. else 0;
  */

  movement.x = keys['a'] ? -1 : (keys['d'] ? 1 : 0) * speedmod;	//if a, left. if d, right. else 0
  movement.y = keys['w'] ? -1 : (keys['s'] ? 1 : 0) * speedmod;	//if w, up. if s, down. else 0;
  coords = coords + movement;
}
Player::~Player() {};











