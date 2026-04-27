#pragma once

#include "vector.h"
#include <iosfwd>

class Triangle {
  public:
    Vector v0;
    Vector v1;
    Vector v2;

    // Конструктор
    Triangle(const Vector& v0, const Vector& v1, const Vector& v2);

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
};