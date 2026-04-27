#include "intersection.h"
#include <cmath>

bool intersectTriangle(const Ray& ray, const Triangle& tri, HitInfo& hit) {

    const float EPS = 1e-6f;

    Vector v0v1 = tri.v1 - tri.v0;
    Vector v0v2 = tri.v2 - tri.v0;

    Vector pvec = ray.direction.cross(v0v2);

    float det = v0v1.dot(pvec);

    if (fabs(det) < EPS) {
        return false;
    }

    float invDet = 1.0f / det;

    Vector tvec = ray.origin - tri.v0;

    float u = tvec.dot(pvec) * invDet;
    if (u < 0 || u > 1)
        return false;

    Vector qvec = tvec.cross(v0v1);

    float v = ray.direction.dot(qvec) * invDet;
    if (v < 0 || u + v > 1)
        return false;

    float t = v0v2.dot(qvec) * invDet;

    if (t < EPS)
        return false;

    hit.t = t;
    hit.position = ray.origin + ray.direction * t;
    hit.normal = v0v1.cross(v0v2).normalize();

    return true;
}