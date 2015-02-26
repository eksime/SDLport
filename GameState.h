#pragma once
#include "GameMode.h"
#include <string>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int MS_PER_UPDATE;

class GameState {
public:
  std::string playerName;
  GAME_MODE gameMode;
  long score;
  long time;
  GameState();
  ~GameState();
};

extern GameState gameState;
extern bool quit;