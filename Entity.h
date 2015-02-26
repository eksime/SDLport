#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <list>

#include "LTexture.h"
#include "Coords.h"

class Entity {
public:
  static std::list<Entity> entities;

  Entity(Coords c);
  ~Entity();

  Coords coords;
  Coords movement;
  float collisionRadius;
  int health;
  int maxHealth;
  bool invincible;

  void render();
  bool setTexture(std::string texture);

private:
  LTexture* texture;
};

class Shark : public Entity {
public:
  Shark(Coords c);
  ~Shark();
};

class Iceberg : public Entity {
public:
  Iceberg(Coords c);
  Iceberg(Coords c, int health);
  ~Iceberg();
private:
  void init(Coords c, int h);
};

class Bullet : public Entity {
  int damage;
public:
  Bullet(Coords c, Coords d, int dmg);
  ~Bullet();
};

class Cthulhu : public Entity {
public:
  Cthulhu(Coords c);
  ~Cthulhu();
};

class Player : public Entity {
public:
  std::string name;
  float speedmod;
  Player(Coords c, int health);
  ~Player();
};








