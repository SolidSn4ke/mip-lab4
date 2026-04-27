#include "color.h"

// Конструктор
Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

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