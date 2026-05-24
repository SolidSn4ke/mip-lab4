#pragma once
#include "color.h"
#include "vector.h"
#include <cstdlib>

/**
 * @brief Площадной источник света в виде треугольника.
 *
 * Свет излучается равномерно по поверхности треугольника.
 */
class LightSource {
  public:
    /**
     * @brief Вершины светящегося треугольника.
     */
    Vector v0, v1, v2;

    /**
     * @brief Интенсивность излучения (radiance / emission).
     *
     * Задаёт, сколько света испускает источник в RGB каналах.
     * Обычно хранится в HDR диапазоне (может быть > 1).
     */
    Color emission;

    /**
     * @brief Создаёт площадной источник света (треугольник).
     *
     * @param v0 первая вершина
     * @param v1 вторая вершина
     * @param v2 третья вершина
     * @param emission интенсивность излучения света
     */
    LightSource(const Vector& v0, const Vector& v1, const Vector& v2, const Color& emission);

    /**
     * @brief Нормаль поверхности света.
     *
     * Используется для освещения и определения стороны излучения.
     */
    Vector getNormal() const;

    /**
     * @brief Случайная точка на поверхности треугольника.
     *
     * Используется для Monte Carlo sampling при area lighting.
     *
     * @return точка на поверхности источника света
     */
    Vector samplePoint() const;

    /**
     * @brief Площадь треугольника света.
     */
    float getArea() const;
};