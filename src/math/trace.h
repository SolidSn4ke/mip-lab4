#pragma once

#include "color.h"
#include "ray.h"
#include "scene.h"
#include "vector.h"

/**
 * @brief Данные о пикселе для пост-процессинга.
 */
struct RenderPixel {
    Color finalColor;
    Color directColor;
    Color indirectColor;
    float depth;
    int objectId;
    Vector normal;
};

/**
 * @brief Трассирует луч через сцену и вычисляет цвет.
 *
 * Проверяет пересечения луча с объектами сцены
 * и рассчитывает освещение в точке попадания.
 *
 * @param ray луч, испускаемый камерой
 * @param scene сцена с геометрией и источниками света
 * @param depth глубина рекурсии
 *
 * @return Итоговый цвет луча
 */
Color trace(const Ray& ray, const Scene& scene, int depth);

/**
 * @brief Трассирует луч и возвращает детальную информацию о первом пересечении.
 *
 * @param ray луч, испускаемый камерой
 * @param scene сцена
 * @param maxDepth максимальная глубина рекурсии
 * @return Структура RenderPixel с данными о первом пересечении и итоговым цветом.
 */
RenderPixel trace_first_hit(const Ray& ray, const Scene& scene, int maxDepth);
