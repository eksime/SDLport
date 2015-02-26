#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <list>

#include "LTexture.h"
#include "Coords.h"

enum ENTITY_TYPE {
  ICEBERG,
  SHARK,
  BULLET,
  CTHULHU,
  PLAYER,
  UPGRADE,
  SHIELD
};

class Entity {
public:
  static std::list<Entity*> entities;

  Entity(Coords c);
  ~Entity();

  ENTITY_TYPE entType;
  Coords coords;
  Coords movement;
  float collisionRadius;
  int health;
  int maxHealth;
  bool invincible;

  bool collisionCheck(Entity*);
  void render();
  bool setTexture(std::string texture);
  virtual void move() {};
  virtual void collide(Entity* e) {};

private:
  LTexture* texture;
};

void addEnt(Entity* e);
