#include "color.h"
#include <algorithm>

// Конструктор
Color::Color(float r, float g, float b)
    : r(std::min(std::max(r, 0.0f), 1.0f)), g(std::min(std::max(g, 0.0f), 1.0f)),
      b(std::min(std::max(b, 0.0f), 1.0f)) {}

// Конвертация в вектор
Vector Color::toVector() const {
    return Vector(r, g, b);
}

// Сложение цветов
Color Color::operator+(const Color& other) const {
    return Color(r + other.r, g + other.g, b + other.b);
}

// Умножение на число
Color Color::operator*(float k) const {
    return Color(r * k, g * k, b * k);
}