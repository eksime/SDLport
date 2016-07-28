#pragma once
#include <SDL.h>
#include "Coords.h"

extern Coords bulletAngle;
extern int menuOption;

void OnMouseClick(SDL_MouseButtonEvent e);
void OnControllerAxis(SDL_JoyAxisEvent e);
void OnKeyDown(SDL_Keycode e);
void OnKeyUp(SDL_Keycode e);
void MouseMotion(SDL_MouseMotionEvent e);
void doMenuAciton(int menuAction);
void init();