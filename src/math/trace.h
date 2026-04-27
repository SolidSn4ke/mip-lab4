#pragma once

#include "color.h"
#include "ray.h"
#include "scene.h"
#include "vector.h"

Color trace(const Ray& ray, const Scene& scene);