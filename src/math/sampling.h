#pragma once

#include "vector.h"
#include <cmath>
#include <cstdlib>

namespace Sampling {
    inline float randomFloat() {
        return (float)rand() / (float)RAND_MAX;
    }

    inline Vector sampleHemisphere(const Vector& normal) {
        float u1 = randomFloat();
        float u2 = randomFloat();

        float r = std::sqrt(u1);
        float theta = 2.0f * 3.1415926535f * u2;

        float x = r * std::cos(theta);
        float y = r * std::sin(theta);
        float z = std::sqrt(1.0f - u1);

        Vector localVector(x, y, z);

        // Create orthonormal basis
        Vector helper = (std::abs(normal.x) > 0.1f) ? Vector(0, 1, 0) : Vector(1, 0, 0);
        Vector tangent = helper.cross(normal).normalize();
        Vector bitangent = normal.cross(tangent);

        return (tangent * localVector.x + bitangent * localVector.y + normal * localVector.z).normalize();
    }
}
