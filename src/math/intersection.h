#pragma once

#include "ray.h"
#include "triangle.h"
#include "vector.h"

/**
 * @brief Информация о пересечении луча с объектом.
 */
struct HitInfo {

    /**
     * @brief Расстояние от начала луча до точки пересечения.
     */
    float t;

    /**
     * @brief Точка пересечения в мировых координатах.
     */
    Vector position;

    /**
     * @brief Нормаль поверхности в точке пересечения.
     *
     * Обычно используется для освещения.
     */
    Vector normal;
};

/**
 * @brief Проверяет пересечение луча с треугольником.
 *
 * Использует алгоритм Мёллера-Трамбора.
 *
 * @param ray луч
 * @param tri треугольник
 * @param hit структура для сохранения информации о пересечении
 *
 * @return true если пересечение найдено
 * @return false если пересечения нет
 */
bool intersectTriangle(const Ray& ray, const Triangle& tri, HitInfo& hit);