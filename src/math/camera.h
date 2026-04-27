#pragma once

#include "ray.h"
#include "vector.h"

class Camera {
  public:
    Vector position;
    Vector forward;
    Vector up;
    Vector right;
    float fov;

    // Конструктор
    Camera(const Vector& pos, const Vector& forward, const Vector& up, const Vector& right,
           float fov);

    Camera(const Vector& pos, const Vector& forward);

    Ray generate_ray(int x, int y, int w, int h);
};