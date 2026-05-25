#pragma once

#include "ray.h"
#include "vector.h"

/**
 * @brief Камера в 3D пространстве.
 *
 * Используется для генерации лучей через пиксели изображения.
 * Камера задаётся позицией и базисом направления (forward/up/right).
 */
class Camera {
  public:
    /**
     * @brief Позиция камеры в мировом пространстве.
     */
    Vector position;

    /**
     * @brief Направление взгляда камеры.
     *
     * Обычно предполагается нормализованным.
     */
    Vector forward;

    /**
     * @brief Верхнее направление камеры.
     *
     * Обычно предполагается нормализованным.
     */
    Vector up;

    /**
     * @brief Правое направление камеры.
     *
     * Обычно предполагается нормализованным и ортогональным
     * к forward и up.
     */
    Vector right;

    /**
     * @brief Вертикальный угол обзора камеры (Field of View).
     *
     * Задаётся в градусах.
     */
    float fov;

    /**
     * @brief Создаёт камеру.
     *
     * @param pos позиция камеры
     * @param forward направление взгляда
     * @param up верхнее направление
     * @param right правое направление
     * @param fov угол обзора в градусах
     */
    Camera(const Vector& pos, const Vector& forward, const Vector& up, const Vector& right,
           float fov);

    /**
     * @brief Генерирует луч через пиксель изображения.
     *
     * @param x координата пикселя по X
     * @param y координата пикселя по Y
     * @param w ширина изображения
     * @param h высота изображения
     *
     * @return Луч, проходящий через пиксель
     */
    Ray generate_ray(int x, int y, int w, int h) const;
};