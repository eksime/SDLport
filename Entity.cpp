#include "Entity.h"
#include "GameState.h"
#include "Mouse.h"
#include "Input.h"

std::list<Entity*> Entity::entities;

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

bool Entity::collisionCheck(Entity* e) {
  return (coords - e->coords).pyth() <= (collisionRadius + e->collisionRadius);
}

Entity::~Entity() {}












