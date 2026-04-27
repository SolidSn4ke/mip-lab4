#pragma once
#include "vector.h"

class LightSource {
  public:
    Vector position;
    Vector direction;
    Vector color;

    // Конструктор
    LightSource(const Vector& position, const Vector& direction, const Vector& color);
};