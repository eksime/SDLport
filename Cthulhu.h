#pragma once
#include "Entity.h"

class Cthulhu : public Entity {
public:
  Cthulhu(Coords c);
  ~Cthulhu();

  void move();
  void collide(Entity* e) {};
};