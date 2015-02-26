#pragma once
#include "Entity.h"

class Shark : public Entity {
public:
  Shark(Coords c);
  ~Shark();

  void move();
  void collide(Entity* e) {};
};
