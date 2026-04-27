#pragma once

#include "vector.h"

class Color {
  public:
    float r, g, b;

    // Конструктор
    Color(float r, float g, float b);

    // Конвертация в вектор
    Vector toVector();
};