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

#include "main.h"
#include "Coords.h"
#include "GameState.h"
#include "LTexture.h"
#include "Entity.h"
#include "Input.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int MS_PER_UPDATE = 16;
bool quit = false;

bool keys[1024];
//Starts up SDL and creates window

//Loads media

//Frees media and shuts down SDL

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gTextArial;

bool initSDL() {
  bool success = true;
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }
    //Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      //Create vsynced renderer for window
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        //Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);


        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }

        //Initialize SDL_ttf
        if (TTF_Init() == -1) {
          printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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

  for (string t : { "player", "shark", "iceberg", "bullet", "cthulhu" }) {
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
  Shark(Coords(50, 50));
  Iceberg(Coords(50, 120));
  Bullet(Coords(50, 180), Coords(), 1);
  Cthulhu(Coords(50, 240));
  Player(Coords(50, 280), 10);


  gameState.gameMode = GAME_STANDARD;
  //gameState.gameMode=GAME_TITANIC;
  gameState.score = 0;
  Player(Coords(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 10);
}

void close() {

  //Free all textures
  for (pair<string, LTexture> t : LTexture::texturePool) {
    t.second.free();
  }

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
  //Clear screen
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);

  //Render arrow
  std::list<Entity>::iterator ent = Entity::entities.begin();
  while (ent != Entity::entities.end()) {
    ent->movement.x = 1;
    ent->movement.y = 1;
    ent->coords = ent->coords + ent->movement;
    ent->render();
    ent++;
  }
 // LTexture::texturePool["arrow"].render((SCREEN_WIDTH - LTexture::texturePool["arrow"].getWidth()) / 2, (SCREEN_HEIGHT - LTexture::texturePool["arrow"].getHeight()) / 2, NULL, 0);

  gTextArial.loadFromRenderedText("Score", { 0, 0, 0 })->render(0, 50);
  //Update screen
  SDL_RenderPresent(gRenderer);
}

void update() {

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
      keys[e.key.keysym.scancode] = true;
      break;

    case SDL_KEYUP:
      keys[e.key.keysym.scancode] = false;
      break;

    case SDL_MOUSEMOTION:

      break;


    }
  }
}

int main(int argc, char* args[]) {
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
          update();
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