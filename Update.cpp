#include <stdlib.h>
#include "GameState.h"
#include "Input.h"
#include "Update.h"
#include "Coords.h"
#include "Tables.h"

#include "Bullet.h"
#include "Iceberg.h"
#include "Shark.h"
#include "Bullet.h"
#include "Player.h"
#include "Cthulhu.h"

int playerInvuln = 0;
long timer = 0;
/**
* Function triggered every 30 ms
* Use for game logic. Drawing from here will not work.
**/

void addEnt(Entity* e) {
  Entity::entities.emplace_back(e);
}

void update_GameMainMenu() {
  // update code for specific game mode 
  // i.e. spawning, triggered every 16ms
}
int  j = 0;
void update_GameStandard() {
  int x;				//current random spawning. could be changed later based on what we want.
  int y;

  long num;
  if (timer % 420 == 0) // every 8 secs
  {
    int i = 0;

    for (i = 0; i <= j; i++) {
      x = rand();
      y = rand();

      if (x>y) {
        addEnt(new Shark(Coords(rand() % SCREEN_WIDTH, 0)));
        addEnt(new Iceberg(Coords(rand() % SCREEN_WIDTH, SCREEN_HEIGHT), 1));
        addEnt(new Shark(Coords(0, rand() % SCREEN_HEIGHT)));
        addEnt(new Iceberg(Coords(SCREEN_WIDTH, rand() % SCREEN_HEIGHT), 1));
      } else {
        addEnt(new Shark(Coords(SCREEN_WIDTH, rand() % SCREEN_HEIGHT)));
        addEnt(new Iceberg(Coords(0, rand() % SCREEN_HEIGHT)));
        addEnt(new Shark(Coords(rand() % SCREEN_WIDTH, SCREEN_HEIGHT)));
        addEnt(new Iceberg(Coords(rand() % SCREEN_WIDTH, 0)));
      }
    }

    j++;

  }
  if (timer % 3150 == 0) {

    addEnt(new Cthulhu(Coords(rand() % SCREEN_WIDTH, 0)));
    //Entity(ENT_UPGRADE, Coords(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT), 1);
  }
  if (timer % 1575 == 0) {
    //Entity(ENT_SHIELD, Coords(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT), 1);  //power ups spwaing
  }
}

void update_GameTitanic() {
  int x;				//current random spawning. could be changed later based on what we want.
  int y;

  long num;
  if (timer % 158 == 0) // every 3 secs
  {

    // int i=0;
    // j=1;
    // for (i =0; i<=j; i++)
    // {
    x = rand();
    y = rand();
    j++;
    if (x>y) {
      addEnt(new Iceberg(Coords(rand() % SCREEN_WIDTH, SCREEN_HEIGHT)));
      addEnt(new Iceberg(Coords(SCREEN_WIDTH, rand() % SCREEN_HEIGHT)));
    } else {
      addEnt(new Iceberg(Coords(0, rand() % SCREEN_HEIGHT)));
      addEnt(new Iceberg(Coords(rand() % SCREEN_WIDTH, 0)));
    }
    // }



  }
  if (timer % 1575 == 0) {
    //power ups spwaning
  }

  int loss = 75 - j;
  if (loss<40)
    loss = 40;
  if (timer %  loss == 0) {
    player->health--;
  }
}

void update_GameSurvival() {
  int x;				//current random spawning. could be changed later based on what we want.
  int y;

  long num;
  if (timer % 420 == 0) // every 8 secs
  {
    int i = 0;

    for (i = 0; i <= j; i++) {
      x = rand();
      y = rand();

      if (x>y) {
        addEnt(new Shark(Coords(rand() % SCREEN_WIDTH, 0)));
        addEnt(new Iceberg(Coords(rand() % SCREEN_WIDTH, SCREEN_HEIGHT), 1));
        addEnt(new Shark(Coords(0, rand() % SCREEN_HEIGHT)));
        addEnt(new Iceberg(Coords(SCREEN_WIDTH, rand() % SCREEN_HEIGHT), 1));
      } else {
        addEnt(new Shark(Coords(SCREEN_WIDTH, rand() % SCREEN_HEIGHT)));
        addEnt(new Iceberg(Coords(0, rand() % SCREEN_HEIGHT)));
        addEnt(new Shark(Coords(rand() % SCREEN_WIDTH, SCREEN_HEIGHT)));
        addEnt(new Iceberg(Coords(rand() % SCREEN_WIDTH, 0)));
      }
    }

    j++;

  }
  if (timer % 3150 == 0) {

    addEnt(new Cthulhu(Coords(rand() % SCREEN_WIDTH, 0)));
  }
  if (timer % 1575 == 0) {
    //power ups spwaning
  }
  if (timer % 53 == 0) {
    gameState.score++;
  }
}

void Update() {
  timer++;
  if (!(timer % 5) && (bulletAngle.x != 0 || bulletAngle.y != 0)) {
    addEnt(new Bullet(player->coords, player->coords + bulletAngle));
  }
  std::list<Entity*>::iterator ent = Entity::entities.begin();
  while (ent != Entity::entities.end()) {
    if ((*ent)->health <= 0 && (*ent)->entType != PLAYER) {
      delete (*ent);
      ent = Entity::entities.erase(ent);

    } else {
      (*ent)->move();
      for (std::list<Entity*>::iterator ent2 = ent; ent2 != Entity::entities.end(); ++ent2) { //for every other element.
        if (*ent != *ent2) {// dont collide with self	
          if ((*ent)->collisionCheck(*ent2)) {						  // if they are touching
            if ((*ent2)->entType == BULLET) {								  // is ent2 a bullet?
              (*ent2)->collide((*ent));							  // trigger collision on the bullet or the object hitting the player.
            } else {// trigger collision normally.
              (*ent)->collide((*ent2));
            }
          }
        }
      }
      ent++;
    }
  }

  //removes any entitie
  if (player->health == 0) {
    updateScores();
    exit(0);

    //leaderboard here
    //go to main menu
    //gameState.gameMode==GAME_MAIN_MENU;
    //exit game
  }

  funcPtr update_Game[] = { &update_GameMainMenu, &update_GameStandard, &update_GameTitanic, &update_GameSurvival };
  update_Game[gameState.gameMode]();

  if (playerInvuln >0) {
    playerInvuln--;			//handles player being invulnrable
  } else
    player->invincible = false;
}