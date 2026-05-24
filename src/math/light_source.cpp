#include "light_source.h"

LightSource::LightSource(const Vector& v0, const Vector& v1, const Vector& v2,
                         const Color& emission)
    : v0(v0), v1(v1), v2(v2), emission(emission) {}

Vector LightSource::getNormal() const {
    return (v1 - v0).cross(v2 - v0).normalize();
}

Vector LightSource::samplePoint() const {
    float r1 = (float)rand() / RAND_MAX;
    float r2 = (float)rand() / RAND_MAX;
    if (r1 + r2 > 1.0f) {
        r1 = 1.0f - r1;
        r2 = 1.0f - r2;
    }
    return v0 + r1 * (v1 - v0) + r2 * (v2 - v0);
}

float LightSource::getArea() const {
    return (v1 - v0).cross(v2 - v0).length() * 0.5f;
}