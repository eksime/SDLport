#pragma once
class Coords {
public:
  Coords();
  Coords(float x, float y);
  ~Coords();

  float x;
  float y;

  float pyth();

  friend float operator ^ (const Coords &c1, const Coords &c2);
  friend Coords operator + (const Coords &c1, const Coords &c2);
  friend Coords operator - (const Coords &c1, const Coords &c2);
};

