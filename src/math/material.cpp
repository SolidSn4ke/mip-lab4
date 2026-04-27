#include "material.h"
#include <algorithm>

// Конструктор
Material::Material(const Color& diffuse, const Color& specular, float shininess)
    : diffuse(diffuse), specular(specular), shininess(shininess) {}