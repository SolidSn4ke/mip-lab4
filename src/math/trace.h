#pragma once

#include "color.h"
#include "ray.h"
#include "scene.h"

/**
 * @brief Трассирует луч через сцену и вычисляет цвет.
 *
 * Проверяет пересечения луча с объектами сцены
 * и рассчитывает освещение в точке попадания.
 *
 * @param ray луч, испускаемый камерой
 * @param scene сцена с геометрией и источниками света
 *
 * @return Итоговый цвет луча
 */
Color trace(const Ray& ray, const Scene& scene);