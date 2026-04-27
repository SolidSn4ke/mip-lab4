#include "triangle.h"
#include <iostream>

// Конструктор
Triangle::Triangle(const Vector& v0, const Vector& v1, const Vector& v2) : v0(v0), v1(v1), v2(v2) {}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    os << "{" << t.v0 << ", " << t.v1 << ", " << t.v2 << "}";
    return os;
}