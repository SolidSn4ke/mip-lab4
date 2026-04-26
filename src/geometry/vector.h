#pragma once

#include <iosfwd>

class Vector {
  public:
    float x, y, z;

    // Конструктор
    Vector(float x = 0, float y = 0, float z = 0);

    // Вывод в консоль
    void print() const;

    // Сложение векторов
    Vector operator+(const Vector& other) const;

    // Вычитание векторов
    Vector operator-(const Vector& other) const;

    // Сравнение векторов
    bool operator==(const Vector& other) const;

    // Умножение вектора на число
    Vector operator*(float k) const;

    // Деление вектора на число
    Vector operator/(float k) const;

    // Векторное произведение
    Vector cross(const Vector& other) const;

    // Длина вектора
    float length() const;

    // Нормализация
    Vector normalize() const;

    // Скалярное произведение
    float dot(const Vector& other) const;

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};