/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string>
#include <cmath>
#include <map>

using namespace std;

#include "Coords.h"
#include "GameState.h"
#include "LTexture.h"
#include "Input.h"
#include "Update.h"

#include "Bullet.h"
#include "Iceberg.h"
#include "Shark.h"
#include "Bullet.h"
#include "Player.h"
#include "Cthulhu.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int MS_PER_UPDATE = 16;
bool quit = false;

bool keys[1024];
Player* player;
//Starts up SDL and creates window

//Loads media

//Frees media and shuts down SDL

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Joystick* gGameController = NULL;

//Scene textures
LTexture gTextArial;

bool initSDL() {
  bool success = true;
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
    printf("Critical: SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }
    //Check for joysticks
    if (SDL_NumJoysticks() < 1) {
      printf("Warning: No joysticks connected!\n");
    } else {
      //Load joystick
      gGameController = SDL_JoystickOpen(0);
      if (gGameController == NULL) {
        printf("Critical: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
      }
    }
    //Create window
    gWindow = SDL_CreateWindow("Sharks n' Icebergs", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Critical: Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      //Create vsynced renderer for window
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
        printf("Critical: Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        //Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);


        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("Critical: SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }

        //Initialize SDL_ttf
        if (TTF_Init() == -1) {
          printf("Critical: SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
          success = false;
        }
        //set texture render target
        LTexture::gRenderer = gRenderer;
      }
    }
  }

  return success;
}

bool loadMedia() {
  //Loading success flag
  bool success = true;

  for (string t : { "player", "shark", "sharkunder", "iceberg", "bullet", "cthulhu" }) {
    LTexture::texturePool[t] = *new LTexture;
    if (!LTexture::texturePool[t].loadFromFile("res/" + t + ".png")) {
      std::cout << "Failed to load " + t + " texture!\n" << std::endl;
      success = false;
    };
  }

  LTexture::gFont = TTF_OpenFont("res/arial.ttf", 14);
  if (LTexture::gFont == NULL) {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  }

  return success;
}


void init() {
  gameState.score = 0;
  int initHP;
  switch (gameState.gameMode) {
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
  addEnt(new Player(Coords(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), initHP));
}

void close() {
  //Free all textures
  for (pair<string, LTexture> t : LTexture::texturePool) {
    t.second.free();
  }

  SDL_JoystickClose(gGameController);
  gGameController = NULL;

  //Destroy window	
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void render() {
  //SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_SetRenderDrawColor(gRenderer, 0, 153, 255, 0xFF);
  SDL_RenderClear(gRenderer);

  std::list<Entity*>::iterator ent = Entity::entities.begin();
  while (ent != Entity::entities.end()) {
    (*ent)->render();
    ent++;
  }

  gTextArial.loadFromRenderedText("Score: " + to_string(gameState.score), { 255, 255, 255 })->render(SCREEN_WIDTH - 100, 30);
  gTextArial.loadFromRenderedText("Health: " + to_string(player->health), { 255, 255, 255 })->render(SCREEN_WIDTH - 220, 30);

  if (player->invincible == true) {
    gTextArial.loadFromRenderedText("Invincible! " + to_string(player->health), { 255, 255, 255 })->render(SCREEN_WIDTH - 320, 30);
  }

  //Update screen
  SDL_RenderPresent(gRenderer);
}

void handleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    //User requests quit
    switch (e.type) {
    case SDL_QUIT:
      quit = true;
      break;

    case SDL_KEYDOWN:
      if (!e.key.repeat)
        OnKeyDown(e.key.keysym.sym);
      break;

    case SDL_KEYUP:
      if (!e.key.repeat)
        OnKeyUp(e.key.keysym.sym);
      break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      OnMouseClick(e.button);
      break;

    case SDL_MOUSEMOTION:
      MouseMotion(e.motion);
      break;

    case SDL_JOYAXISMOTION:
      OnControllerAxis(e.jaxis);
      break;

    case SDL_CONTROLLERBUTTONDOWN:
    case SDL_CONTROLLERBUTTONUP:
      break;

    }
  }
}

int main(int argc, char* args[]) {

#ifndef _DEBUG
  if (argc == 1) exit(0);
  gameState.gameMode = (GAME_MODE)atoi(args[1]);
  gameState.playerName = args[2];
#else
  gameState.gameMode = GAME_STANDARD;
  gameState.playerName = "DEBUG";
#endif

  //Start up SDL and create window
  if (!initSDL()) {
    printf("Failed to initialize!\n");
  } else {
    //Load media
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {

      init();

      double previous = clock();
      double lag = 0.0;
      while (!quit) {

        double current = clock();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        handleEvents();

        while (lag >= MS_PER_UPDATE) {
          Update();
          lag -= MS_PER_UPDATE;
        }

        render();
      }
    }
  }

  //Free resources and close SDL
  close();

  return 0;
}