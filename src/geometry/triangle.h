#pragma once

#include "vector.h"

class Triangle {
  public:
    Vector v0;
    Vector v1;
    Vector v2;

    // Конструктор
    Triangle(const Vector& v0, const Vector& v1, const Vector& v2);
};