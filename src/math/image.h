#pragma once

#include "color.h"
#include <vector>

class Image {
  public:
    int width, height;
    std::vector<Color> pixels;

    // Конструктор
    Image(int width, int height);

    // Установить цвет пикселя
    void setPixel(int x, int y, const Color& c);

    // Получить цвет пикселя
    const Color& getPixel(int x, int y) const;
};