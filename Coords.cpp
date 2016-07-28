#include "Coords.h"
#include <math.h>

Coords::Coords() {
  x = 0;
  y = 0;
}

Coords::Coords(float nx, float ny) {
  x = nx;
  y = ny;
}

float Coords::pyth() {
  return sqrtf(x * x + y * y);
}

Coords::~Coords() {}

float operator ^ (const Coords &c1, const Coords &c2) {
  Coords t = c1 - c2;
  return t.pyth();
}

Coords operator + (const Coords &c1, const Coords &c2) {
  return Coords(c1.x + c2.x, c1.y + c2.y);
}

Coords operator - (const Coords &c1, const Coords &c2) {
  return Coords(c1.x - c2.x, c1.y - c2.y);
}

