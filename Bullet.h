#pragma once
#include "Entity.h"

class Bullet : public Entity {
  int damage;
public:
  Bullet(Coords c, Coords d);
  ~Bullet();

  void move();
  void collide(Entity* e);
};
