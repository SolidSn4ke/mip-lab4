#include "trace.h"
#include "intersection.h"
#include <algorithm>
#include <limits>

Color trace(const Ray& ray, const Scene& scene) {
    float closestT = std::numeric_limits<float>::max();
    bool hitSomething = false;

    HitInfo bestHit;

    // 1. ищем ближайшее пересечение
    for (const auto& tri : scene.triangles) {
        HitInfo hit;

        if (intersectTriangle(ray, tri, hit)) {
            if (hit.t < closestT) {
                closestT = hit.t;
                bestHit = hit;
                hitSomething = true;
            }
        }
    }

    // 2. если ничего не нашли → фон
    if (!hitSomething) {
        return Color(0.0f, 0.0f, 0.0f); // чёрный фон
    }

    // 3. базовый свет (Lambert)
    Color result(0.0f, 0.0f, 0.0f);

    for (const auto& light : scene.lights) {

        Vector lightDir = (light.position - bestHit.position).normalize();

        float diff = std::max(0.0f, bestHit.normal.dot(lightDir));

        // расстояние до света (можно позже для теней)
        Color lightColor = light.color;

        result = result + lightColor * diff;
    }

    return result;
}