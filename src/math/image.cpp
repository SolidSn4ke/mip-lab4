#include "image.h"

// Конструктор
Image::Image(int width, int height, const std::vector<Color>& pixels)
    : width(width), height(height), pixels(pixels) {}