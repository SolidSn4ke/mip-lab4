#pragma once

#include "ray.h"
#include "triangle.h"
#include "vector.h"

struct HitInfo {
    float t;
    Vector position;
    Vector normal;
};

bool intersectTriangle(const Ray& ray, const Triangle& tri, HitInfo& hit);