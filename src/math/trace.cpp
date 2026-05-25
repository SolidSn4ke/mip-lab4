#include "trace.h"
#include "intersection.h"
#include "sampling.h"
#include <algorithm>
#include <limits>

#define PI 3.14f

#define BLACK Color(0.0f, 0.0f, 0.0f)

Color trace(const Ray& ray, const Scene& scene, int depth) {
    // Завершаем рекурсию
    if (depth <= 0) {
        return BLACK;
    }

    // Погрешность
    const float EPS = 1e-6f;

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

        // BRDF
        Color brdf = closest_material.diffuseColor / PI;

        Color light_contrib = light.emission * NdotL;

        result = result + brdf * light_contrib;
    }

    // Русская рулетка
    float p = std::max({closest_material.diffuseColor.r, closest_material.diffuseColor.g,
                        closest_material.diffuseColor.b});

    // Выравнивание
    if (p < 0.1f) {
        p = 0.1f;
    }

    if (p > 0.9f) {
        p = 0.9f;
    }

    if (rand01() > p) {
        return result;
    }

    // Учитываем глобальное освещение
    float p_spec = closest_material.specularCoeff;
    p_spec /= 100;

    Vector newDir;
    if (rand01() < p_spec) {
        // SPECULAR
        newDir = ray.direction - normal * (2.0f * ray.direction.dot(normal));
    } else {
        // DIFFUSE
        newDir = sampleHemisphere(normal);
    }

    // Новый луч из точки пересечения
    Ray indirectRay(hit_point + normal * EPS, newDir);

    // Рекурсивный вызов
    Color indirect = trace(indirectRay, scene, depth - 1);

    indirect = indirect / p;

    // BRDF
    float cosTheta = std::max(normal.dot(newDir), 0.0f);
    Color brdf = closest_material.diffuseColor / PI;

    result = result + indirect * brdf * cosTheta;
    return result;
}