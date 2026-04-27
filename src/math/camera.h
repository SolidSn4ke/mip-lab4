#pragma once

#include "vector.h"

class Camera {
  public:
    Vector position;
    Vector forward;

    // Конструктор
    Camera(const Vector& position, const Vector& forward);
};