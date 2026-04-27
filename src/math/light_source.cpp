#include "light_source.h"

// Конструктор
LightSource::LightSource(const Vector& position, const Vector& direction, const Vector& color)
    : position(position), direction(direction), color(color) {}