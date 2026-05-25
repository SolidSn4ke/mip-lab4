#include "trace.h"
#include "intersection.h"
#include "sampling.h"
#include <algorithm>
#include <limits>

#define PI 3.14f

#define BLACK Color(0.0f, 0.0f, 0.0f)

Color trace(const Ray& ray, const Scene& scene) {

    const float EPS = 1e-6f; // Погрешность

    // Ищем ближайшее пересечение
    float shortest_distance = std::numeric_limits<float>::max();
    HitInfo closest_hit;
    Material closest_material;
    bool hit_found = false;

    // Поиск ближайшего треугольника
    for (const Triangle& triangle : scene.triangles) {
        HitInfo hit;
        if (intersectTriangle(ray, triangle, hit)) {
            if (hit.t > EPS && hit.t < shortest_distance) {
                shortest_distance = hit.t;
                closest_hit = hit;
                closest_material = triangle.material;
                hit_found = true;
            }
        }
    }

    // Если ничего не пересекли
    if (!hit_found) {
        return BLACK;
    }

    // Точка пересечения
    Vector hit_point = ray.origin + ray.direction * closest_hit.t;

    // Нормаль поверхности
    Vector normal = closest_hit.normal.normalize();

    Color result = BLACK;

    // Освещение от всех источников света
    for (LightSource light : scene.lights) {

        Vector light_position = light.samplePoint();

        Vector to_light = light_position - hit_point;

        float light_distance = to_light.length();

        to_light = to_light.normalize();

        // Луч от точки пересечения к источнику света
        Ray shadow_ray(hit_point + normal * EPS, to_light);

        bool in_shadow = false;

        // Проверяем пересечения до источника света
        for (const Triangle& triangle : scene.triangles) {
            HitInfo shadow_hit;
            if (intersectTriangle(shadow_ray, triangle, shadow_hit)) {
                if (shadow_hit.t > EPS && shadow_hit.t < light_distance) {
                    in_shadow = true;
                    break;
                }
            }
        }

        // Если точка в тени
        if (in_shadow) {
            continue;
        }

        // Закон Ламберта
        float NdotL = std::max(normal.dot(to_light), 0.0f);

        Color diffuse = closest_material.diffuseColor * light.emission * NdotL;

        result = result + diffuse;
    }

    // Учитываем глобавльное освещение
    Vector newDir = sampleHemisphere(normal);

    // Новый луч из точки пересечения
    Ray indirectRay(hit_point + normal * EPS, newDir);

    // Рекурсивный вызов
    Color indirect = trace(indirectRay, scene);

    // BRDF
    float cosTheta = std::max(normal.dot(newDir), 0.0f);
    Color brdf = closest_material.diffuseColor / PI;

    result = result + indirect * brdf * cosTheta;
    return result;
}