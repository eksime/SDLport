#include "Input.h"
#include "Bullet.h"
#include "Player.h"
#include "Mouse.h"
#include "GameState.h"

Coords bulletAngle;

void OnMouseClick(SDL_MouseButtonEvent e) {
  if (gameState.gameMode != GAME_TITANIC)
    addEnt(new Bullet(player->coords, mouse.coords));
}

void OnKeyDown(SDL_Keycode e) {
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
  switch (e) {
  case 27:
    player->health = 0;
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
}

// This is called when the mouse is moved.
void MouseMotion(SDL_MouseMotionEvent e) {
  mouse.coords.x = e.x;
  mouse.coords.y = e.y;
}

void OnControllerAxis(SDL_JoyAxisEvent e) {
  switch (e.axis) {
  case 0:
    player->movement.x = e.value / 32767.0f;
    break;
  case 1:
    player->movement.y = e.value / 32767.0f;
    break;
  case 2:
    bulletAngle.x = e.value / 32767.0f;
    break;
  case 3:
    bulletAngle.y = e.value / 32767.0f;
    break;
  }
}
/*
void XInput() {
  float rx = GAMEPAD_RIGHT_X, ry = GAMEPAD_RIGHT_Y;

  xinputTimer++;
  if (!(xinputTimer % 5))
    if (fabsf(rx) > 0.5 || fabsf(ry) > 0.5)
      OnMouseClick(0, 0, 0, 0);
}
*/