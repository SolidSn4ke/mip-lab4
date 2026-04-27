#include "image.h"

// Конструктор
Image::Image(int width, int height) : width(width), height(height), pixels(width * height) {}

// Установить цвет пикселя
void Image::setPixel(int x, int y, const Color& c) {
    pixels[y * width + x] = c;
}

// Получить цвет пикселя
const Color& Image::getPixel(int x, int y) const {
    return pixels[y * width + x];
}