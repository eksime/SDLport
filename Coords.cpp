#include "Coords.h"


Coords::Coords() {
  x = 0;
  y = 0;
}

Coords::Coords(float nx, float ny) {
  x = nx;
  y = ny;
}

Coords::~Coords() {}

Coords operator + (const Coords &c1, const Coords &c2) {
  return Coords(c1.x + c2.x, c1.y + c2.y);
}

Coords operator - (const Coords &c1, const Coords &c2) {
  return Coords(c1.x - c2.x, c1.y - c2.y);
}

