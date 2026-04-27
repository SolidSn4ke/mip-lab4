#pragma once

#include "color.h"
#include <vector>

class Image {
  public:
    int width, height;
    std::vector<Color> pixels;

    // Конструктор
    Image(int width, int height, const std::vector<Color>& pixels);
};