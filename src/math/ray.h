#pragma once

#include "vector.h"

/**
 * @brief Луч в 3D пространстве.
 *
 * Используется в трассировке лучей для пересечения с геометрией сцены.
 * Луч задаётся точкой начала (origin) и направлением (direction).
 */
class Ray {
  public:
    /**
     * @brief Точка начала луча в пространстве.
     */
    Vector origin;

    /**
     * @brief Направление луча.
     *
     * Обычно предполагается нормализованным.
     */
    Vector direction;

    /**
     * @brief Создаёт луч из точки и направления.
     *
     * @param origin начало луча
     * @param direction направление луча
     */
    Ray(const Vector& origin, const Vector& direction);
};