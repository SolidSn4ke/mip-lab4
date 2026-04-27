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

    Ray generate_ray(float x, float y, int w, int h);
};