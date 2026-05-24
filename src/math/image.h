#pragma once

#include <vector>

/**
 * @brief Двумерное изображение с пикселями произвольного типа.
 *
 * Класс изображения, который хранит пиксели в
 * линейном массиве и предоставляет доступ по (x, y).
 *
 * Тип T определяет формат пикселя:
 * - Color: HDR/linear цвет (float/double)
 * - RGB8:  8-битный цвет для вывода
 *
 * @tparam T Тип пикселя изображения
 */
template <typename T> class Image {
  public:
    int width, height;
    std::vector<T> pixels;

    /**
     * @brief Создаёт изображение заданного размера.
     *
     * Пиксели инициализируются значениями по умолчанию для типа T.
     *
     * @param width Ширина изображения
     * @param height Высота изображения
     */
    Image(int width, int height) : width(width), height(height), pixels(width * height) {}

    /**
     * @brief Устанавливает значение пикселя в координатах (x, y).
     *
     * @param x Координата X (0 ≤ x < width)
     * @param y Координата Y (0 ≤ y < height)
     * @param c Значение пикселя
     */
    void setPixel(int x, int y, const T& c) { pixels[y * width + x] = c; }

    /**
     * @brief Возвращает значение пикселя в координатах (x, y).
     *
     * @param x Координата X (0 ≤ x < width)
     * @param y Координата Y (0 ≤ y < height)
     * @return Константная ссылка на пиксель
     */
    const T& getPixel(int x, int y) const { return pixels[y * width + x]; }
};