#pragma once

#include "color.h"

class Material {
  public:
    Color diffuse;   // Диффузная составляющая
    Color specular;  // Зеркальная составляющая
    float shininess; // Блеск

    // Конструктор
    Material(const Color& diffuse, const Color& specular, float shininess);
};