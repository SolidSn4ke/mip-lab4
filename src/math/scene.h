#pragma once

#include "light_source.h"
#include "triangle.h"
#include <vector>

/**
 * @brief 3D сцена для рендеринга.
 *
 * Содержит геометрию сцены и источники света.
 */
class Scene {
  public:
    /**
     * @brief Треугольники сцены.
     *
     * Используются как основная геометрия
     * для пересечения лучей.
     */
    std::vector<Triangle> triangles;

    /**
     * @brief Источники света сцены.
     *
     * Используются при вычислении освещения.
     */
    std::vector<LightSource> lights;

    /**
     * @brief Создаёт сцену.
     *
     * @param triangles геометрия сцены
     * @param lights источники света
     */
    Scene(const std::vector<Triangle>& triangles, const std::vector<LightSource> lights);
};