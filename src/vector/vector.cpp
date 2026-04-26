#include <cmath>
#include <iostream>

class Vector {
  public:
    float x;
    float y;
    float z;

    // Конструктор
    Vector(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    // Вывод в консоль
    void print() const { std::cout << "(" << x << ", " << y << ", " << z << ")\n"; }

    // Сложение векторов
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    // Вычитание векторов
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    // Сравнение векторов
    bool operator==(const Vector& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Умножение вектора на число
    Vector operator*(float k) const { return Vector(x * k, y * k, z * k); }

    // Деление вектора на число
    Vector operator/(float k) const { return Vector(x / k, y / k, z / k); }

    // Векторное произведение
    Vector cross(const Vector& other) const {
        return Vector(y * other.z - z * other.y, z * other.x - x * other.z,
                      x * other.y - y * other.x);
    }

    // Длина вектора
    float length() const { return std::sqrt(x * x + y * y + z * z); }

    // Нормализация
    Vector normalize() const {
        float len = length();
        if (len == 0) {
            return Vector(0, 0, 0);
        }
        return *this / len;
    }

    // Скалярное произведение
    float dot(const Vector& other) const { return x * other.x + y * other.y + z * other.z; }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};

// Реализация оператора вывода
// Вне класса, так как оператор << не может быть методом класса
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}