#include "color.h"
#include <algorithm>

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color Color::operator+(const Color& other) const {
    return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator*(float k) const {
    return Color(r * k, g * k, b * k);
}

Color Color::operator*(const Color& other) const {
    return Color(r * other.r, g * other.g, b * other.b);
}