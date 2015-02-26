#include "Entity.h"
#include "main.h"

std::list<Entity> Entity::entities;

bool Entity::setTexture(std::string t) {
  if (!LTexture::texturePool.count(t))
    return false;

  texture = &LTexture::texturePool[t];
  return true;
}

void Entity::render() {
  if (texture)
    texture->render(coords.x - (texture->getWidth() / 2), coords.y - (texture->getHeight() / 2), NULL, atan2f(movement.y, movement.x) * 57.2957795f);
}

Entity::Entity(Coords c) {
  texture = (LTexture*)(0);
  coords = c;
}
Entity::~Entity() {}

Shark::Shark(Coords c) : Entity(c) {
  setTexture("shark");
  health = 1;
  maxHealth = 1;
  invincible = false;
  entities.emplace_back(*this);
}
Shark::~Shark() {};

Iceberg::Iceberg(Coords c) : Entity(c) { init(c, 1); }
Iceberg::Iceberg(Coords c, int h) : Entity(c) { init(c, h); }
void Iceberg::init(Coords c, int h) {
  setTexture("iceberg");
  health = h;
  maxHealth = h;
  invincible = false;
  entities.emplace_back(*this);
}
Iceberg::~Iceberg() {};

Bullet::Bullet(Coords c, Coords d, int dmg) : Entity(c) {
  setTexture("bullet");
  health = 1;
  damage = dmg;
  maxHealth = 1;
  invincible = false;
  entities.emplace_back(*this);
}
Bullet::~Bullet() {};

Cthulhu::Cthulhu(Coords c) : Entity(c) {
  setTexture("cthulhu");
  health = 100;
  maxHealth = 100;
  invincible = false;
  entities.emplace_back(*this);
}
Cthulhu::~Cthulhu() {};

Player::Player(Coords c, int h) : Entity(c) {
  setTexture("player");
  name = "Player";
  speedmod = 1;
  health = h;
  maxHealth = h;
  invincible = false;
  entities.emplace_back(*this);
}
Player::~Player() {};












