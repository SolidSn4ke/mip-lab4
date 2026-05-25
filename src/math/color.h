#pragma once

#include "vector.h"

/**
 * @brief Цвет в линейном (HDR) пространстве.
 *
 * Используется в рендеринге для хранения физически корректных значений освещённости.
 * Значения могут выходить за пределы [0;1] и нормализуются позже (например, постпроцессингом).
 */
class Color {
  public:
    /**
     * @brief Компоненты цвета (RGB).
     */
    float r, g, b;

    /**
     * @brief Создаёт цвет.
     *
     * @param r красный канал
     * @param g зелёный канал
     * @param b синий канал
     */
    Color(float r = 0, float g = 0, float b = 0);

    /**
     * @brief Сложение цветов (аддитивное смешивание света).
     */
    Color operator+(const Color& other) const;

    /**
     * @brief Умножение цвета на скаляр (масштабирование яркости).
     */
    Color operator*(float k) const;

    /**
     * @brief Поэлементное умножение цветов (используется в shading/BRDF).
     */
    Color operator*(const Color& other) const;

    /**
     * @brief Деление цвета на скаляр (масштабирование яркости).
     */
    Color operator/(float k) const;
};