#include "Input.h"
#include "Entity.h"
#include "Mouse.h"

int bulletDmg = 1;

void OnMouseClick(SDL_MouseButtonEvent e) {
 // if (gameState.gameMode != GAME_TITANIC)
    Bullet(Coords(mouse.coords),Coords(), 1 * bulletDmg);
}

// This is called when the mouse is moved.
void MouseMotion(SDL_MouseMotionEvent e) {
  mouse.coords.x = e.x;
  mouse.coords.y = e.y;
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