#pragma once
#include "Coords.h"

class Mouse {
public:
  Coords coords;
  bool btn1;
  bool btn2;
  Mouse();
  ~Mouse();
};

extern Mouse mouse;