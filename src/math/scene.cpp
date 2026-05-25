#include "scene.h"

Scene::Scene(const std::vector<Triangle>& triangles, const std::vector<LightSource> lights)
    : triangles(triangles), lights(lights) {}