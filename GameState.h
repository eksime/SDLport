#pragma once
#include "GameMode.h"

class GameState {
public:
  GAME_MODE gameMode;
  long score;
  long time;
  GameState();
  ~GameState();
};

extern GameState gameState;