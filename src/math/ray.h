#pragma once

#include "vector.h"

class Ray {
  public:
    Vector origin;
    Vector direction;

    // Конструктор
    Ray(const Vector& origin, const Vector& direction);
};