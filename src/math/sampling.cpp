#include "sampling.h"
#include <cmath>

#define PI 3.14

void createOrthonormalBasis(const Vector& N, Vector& T, Vector& B) {
    Vector up = (fabs(N.y) < 0.999f) ? Vector(0, 1, 0) : Vector(1, 0, 0);

    T = up.cross(N).normalize();
    B = N.cross(T);
}

float rand01() {
    return rand() / (float)RAND_MAX;
}

Vector sampleHemisphere(const Vector& normal) {

    float u1 = rand01();
    float u2 = rand01();

    float r = std::sqrt(u1);
    float theta = 2.0f * PI * u2;

    float x = r * std::cos(theta);
    float y = r * std::sin(theta);
    float z = std::sqrt(std::max(0.0f, 1.0f - u1));

    // локальный координатный базис
    Vector tangent, bitangent;

    createOrthonormalBasis(normal, tangent, bitangent);

    // перевод из локального пространства в мировое
    return (tangent * x + bitangent * y + normal * z).normalize();
}