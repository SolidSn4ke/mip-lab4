#pragma once

#include <iosfwd>

/**
 * @brief 3D-вектор для математических операций (геометрия, рендеринг).
 *
 * Используется для представления точек, направлений и нормалей.
 */
class Vector {
  public:
    /**
     * @brief Компоненты вектора.
     */
    float x, y, z;

    /**
     * @brief Создаёт вектор.
     * @param x координата X
     * @param y координата Y
     * @param z координата Z
     */
    Vector(float x = 0, float y = 0, float z = 0);

    /**
     * @brief Выводит вектор в консоль (debug).
     */
    void print() const;

    /**
     * @brief Сложение векторов.
     */
    Vector operator+(const Vector& other) const;

    /**
     * @brief Вычитание векторов.
     */
    Vector operator-(const Vector& other) const;

    /**
     * @brief Проверка на равенство (точное сравнение).
     */
    bool operator==(const Vector& other) const;

    /**
     * @brief Умножение вектора на скаляр.
     */
    Vector operator*(float k) const;

    /**
     * @brief Деление вектора на скаляр.
     */
    Vector operator/(float k) const;

    /**
     * @brief Векторное произведение (cross product).
     */
    Vector cross(const Vector& other) const;

    /**
     * @brief Длина (модуль) вектора.
     */
    float length() const;

    /**
     * @brief Нормализованный вектор (длина = 1).
     */
    Vector normalize() const;

    /**
     * @brief Скалярное произведение (dot product).
     */
    float dot(const Vector& other) const;

    /**
     * @brief Вывод в поток (например std::cout).
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};

/**
 * @brief Умножение скаляра на вектор.
 */
inline Vector operator*(float k, const Vector& v) {
    return v * k;
}