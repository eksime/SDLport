#pragma once
#include "Entity.h"

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

extern Player* player;