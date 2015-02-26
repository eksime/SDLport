#pragma once
#include "Entity.h"

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
