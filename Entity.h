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

class Shark : public Entity {
public:
  Shark(Coords c);
  ~Shark();

  void move();
  void collide(Entity* e) {};
};

class Iceberg : public Entity {
public:
  Iceberg(Coords c);
  Iceberg(Coords c, int health);
  ~Iceberg();

  void move();
  void collide(Entity* e);
private:
  void init(Coords c, int h);
};

class Bullet : public Entity {
  int damage;
public:
  Bullet(Coords c, Coords d);
  ~Bullet();

  void move();
  void collide(Entity* e);
};

class Cthulhu : public Entity {
public:
  Cthulhu(Coords c);
  ~Cthulhu();

  void move();
  void collide(Entity* e) {};
};

class Player : public Entity {
public:
  Player(Coords c, int health);
  ~Player();

  void move();
  void collide(Entity* e);

  std::string name;
  int playerInvuln;
  int damage;
  float speedmod;
};

void addEnt(Entity* e);
extern Player* player;
