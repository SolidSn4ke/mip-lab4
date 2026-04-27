#pragma once

#include "light_source.h"
#include "triangle.h"
#include <vector>

class Scene {
  public:
    std::vector<Triangle> triangles;
    std::vector<LightSource> lights;

    // Конструктор
    Scene(const std::vector<Triangle>& triangles, const std::vector<LightSource> lights);
};