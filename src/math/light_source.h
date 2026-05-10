#pragma once
#include "color.h"
#include "vector.h"
#include <cstdlib>

class LightSource {
  public:
    Vector v0, v1, v2; // Vertices of the light triangle
    Color color;

    LightSource(const Vector& v0, const Vector& v1, const Vector& v2, const Color& color)
        : v0(v0), v1(v1), v2(v2), color(color) {}

    Vector getNormal() const { return (v1 - v0).cross(v2 - v0).normalize(); }

    Vector samplePoint() const {
        float r1 = (float)rand() / RAND_MAX;
        float r2 = (float)rand() / RAND_MAX;
        if (r1 + r2 > 1.0f) {
            r1 = 1.0f - r1;
            r2 = 1.0f - r2;
        }
        return v0 + r1 * (v1 - v0) + r2 * (v2 - v0);
    }

    float getArea() const { return (v1 - v0).cross(v2 - v0).length() * 0.5f; }
};