#include "Player.h"
#include "GameState.h"
#include "Input.h"

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
