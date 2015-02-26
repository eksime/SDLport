#pragma once
#include "GameMode.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int MS_PER_UPDATE;

class GameState {
public:

  GAME_MODE gameMode;
  long score;
  long time;
  GameState();
  ~GameState();
};

extern GameState gameState;
extern bool quit;