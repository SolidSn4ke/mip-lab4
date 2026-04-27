#pragma once

#include "vector.h"

class Color {
  public:
    float r, g, b;

    // Конструктор
    Color(float r = 0, float g = 0, float b = 0);

    // Конвертация в вектор
    Vector toVector() const;

    // Сложение цветов
    Color operator+(const Color& other) const;

    // Умножение на число
    Color operator*(float k) const;
};