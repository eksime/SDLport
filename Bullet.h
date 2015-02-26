#pragma once
#include "Entity.h"

class Bullet : public Entity {
  int damage;
  Coords target;
public:
  Bullet(Coords c, Coords t);
  ~Bullet();

  void move();
  void collide(Entity* e);
};
