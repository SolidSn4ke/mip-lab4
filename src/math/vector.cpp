#include "vector.h"
#include <cmath>
#include <iostream>

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

void Vector::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}

Vector Vector::operator+(const Vector& other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
}

bool Vector::operator==(const Vector& other) const {
    return x == other.x && y == other.y && z == other.z;
}

Vector Vector::operator*(float k) const {
    return Vector(x * k, y * k, z * k);
}

Vector Vector::operator/(float k) const {
    return Vector(x / k, y / k, z / k);
}

Vector Vector::cross(const Vector& other) const {
    return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

float Vector::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize() const {
    float len = length();
    if (len == 0) {
        return Vector(0, 0, 0);
    }
    return *this / len;
}

float Vector::dot(const Vector& other) const {
    return x * other.x + y * other.y + z * other.z;
}

// Реализация оператора вывода
// Вне класса, так как оператор << не может быть методом класса
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}