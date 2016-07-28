#include "Input.h"
#include "Bullet.h"
#include "Player.h"
#include "Mouse.h"
#include "GameState.h"
#include "Update.h"
#include <limits.h>
#include <iostream>

Coords bulletAngle;
int menuOption = 0;

void OnMouseClick(SDL_MouseButtonEvent e) {
  if (gameState.gameMode != GAME_TITANIC && gameState.gameMode != GAME_MAIN_MENU)
    addEnt(new Bullet(player->coords, mouse.coords));
}

void init() {
  Entity::entities.clear();
  gameState.score = 0;
  int initHP;
  switch (gameState.gameMode) {
  case GAME_MAIN_MENU:
    initHP = 0;
    break;
  case GAME_STANDARD:
    initHP = 3;
    break;
  case GAME_SURVIVAL:
    initHP = 1;
    break;
  case GAME_TITANIC:
    initHP = 10;
    break;
  }
  maxSpawns = 0;
  timer = 0;
  addEnt(new Player(Coords(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), initHP));
}

void  doMenuAction(int menuOption) {
  if (gameState.gameMode != GAME_MAIN_MENU) return;

  if (menuOption == 4) {
    quit = true;
    return;
  }

  gameState.gameMode = (GAME_MODE)menuOption;
  init();
}

void OnKeyDown(SDL_Keycode e) {
  if (gameState.gameMode != GAME_MAIN_MENU)
    switch (e) {
    case 'w':
      player->movement.y--;
      break;
    case 'a':
      player->movement.x--;
      break;
    case 's':
      player->movement.y++;
      break;
    case 'd':
      player->movement.x++;
      break;
    }
}

void OnKeyUp(SDL_Keycode e) {
  if (gameState.gameMode != GAME_MAIN_MENU) {
    switch (e) {
    case SDLK_ESCAPE:
      player->health = 0;
      quit = true;
      break;
    case 'w':
      player->movement.y++;
      break;
    case 'a':
      player->movement.x++;
      break;
    case 's':
      player->movement.y--;
      break;
    case 'd':
      player->movement.x--;
      break;
    }
  } else {
    switch (e) {
    case SDLK_ESCAPE:
      quit = true;
      break;
    case SDLK_DOWN: //downarrow
      if (menuOption < 3)
        menuOption++;
      break;
    case SDLK_UP: //uparrow
      if (menuOption > 0)
        menuOption--;
      break;
    case SDLK_RETURN: //enter
      doMenuAction(menuOption + 1);
      break;
    }
  }
}

// This is called when the mouse is moved.
void MouseMotion(SDL_MouseMotionEvent e) {
  mouse.coords.x = e.x;
  mouse.coords.y = e.y;
}

void OnControllerAxis(SDL_JoyAxisEvent e) {
  float norm = fmaxf(-1.0f, e.value / -(float)SHRT_MIN);
  float dz = 0.15f;
  float amt = (fabsf(norm) < dz ? 0 : (fabsf(norm) - dz) * (norm / fabsf(norm)));

  switch (e.axis) {
  case 0:
    player->movement.x = amt;
    break;
  case 1:
    player->movement.y = amt;
    break;
  case 2:
    bulletAngle.x = amt;
    break;
  case 3:
    bulletAngle.y = amt;
    break;
  }
}
