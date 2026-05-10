#pragma once

#include "vector.h"
#include "color.h"
#include <iosfwd>

struct Material {
    Color diffuseColor = Color(0.8f, 0.8f, 0.8f);
    float specularCoeff = 0.0f; // 0 = pure diffuse, 1 = pure mirror
};

class Triangle {
  public:
    Vector v0;
    Vector v1;
    Vector v2;
    Material material;

    Triangle(const Vector& v0, const Vector& v1, const Vector& v2)
        : v0(v0), v1(v1), v2(v2) {}

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
};
