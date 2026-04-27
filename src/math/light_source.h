#pragma once
#include "color.h"
#include "vector.h"

class LightSource {
  public:
    Vector position;
    Vector direction;
    Color color;

    // Конструктор
    LightSource(const Vector& position, const Vector& direction, const Color& color);
};