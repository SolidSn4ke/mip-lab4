#include "color.h"

// Конструктор
Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

// Конвертация в вектор
Vector Color::toVector() {
    return Vector(r, g, b);
}