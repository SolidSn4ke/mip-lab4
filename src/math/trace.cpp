#include "trace.h"
#include "intersection.h"
#include "sampling.h"
#include <algorithm>
#include <limits>

#define PI 3.14f

#define BLACK Color(0.0f, 0.0f, 0.0f)

RenderPixel trace_first_hit(const Ray& ray, const Scene& scene, int maxDepth) {
    const float EPS = 1e-6f;
    float shortest_distance = std::numeric_limits<float>::max();
    HitInfo closest_hit;
    Material closest_material;
    int closest_id = -1;
    bool hit_found = false;

    for (size_t i = 0; i < scene.triangles.size(); ++i) {
        HitInfo hit;
        if (intersectTriangle(ray, scene.triangles[i], hit)) {
            if (hit.t > EPS && hit.t < shortest_distance) {
                shortest_distance = hit.t;
                closest_hit = hit;
                closest_material = scene.triangles[i].material;
                closest_id = (int)i;
                hit_found = true;
            }
        }
    }

    if (!hit_found) {
        return {BLACK, BLACK, BLACK, 0.0f, -1, Vector(0, 0, 0)};
    }

    Vector hit_point = ray.origin + ray.direction * closest_hit.t;
    Vector normal = closest_hit.normal.normalize();
    Color direct_color = BLACK;

    for (LightSource light : scene.lights) {
        Vector light_position = light.samplePoint();
        Vector to_light = light_position - hit_point;
        float light_distance = to_light.length();
        to_light = to_light.normalize();

        Ray shadow_ray(hit_point + normal * EPS, to_light);
        bool in_shadow = false;
        for (const Triangle& triangle : scene.triangles) {
            HitInfo shadow_hit;
            if (intersectTriangle(shadow_ray, triangle, shadow_hit)) {
                if (shadow_hit.t > EPS && shadow_hit.t < light_distance) {
                    in_shadow = true;
                    break;
                }
            }
        }

        if (in_shadow)
            continue;

        float NdotL = std::max(normal.dot(to_light), 0.0f);
        Color brdf = closest_material.diffuseColor / PI;
        Color light_contrib = light.emission * NdotL;
        direct_color = direct_color + brdf * light_contrib;
    }

    float p = std::max({closest_material.diffuseColor.r, closest_material.diffuseColor.g,
                        closest_material.diffuseColor.b});
    p = std::max(0.1f, std::min(p, 0.9f));

    Color indirect_color = BLACK;
    if (rand01() < p) {
        Vector newDir;
        float p_spec = closest_material.specularCoeff / 100.0f;
        if (rand01() < p_spec) {
            newDir = ray.direction - normal * (2.0f * ray.direction.dot(normal));
        } else {
            newDir = sampleHemisphere(normal);
        }
        Ray indirectRay(hit_point + normal * EPS, newDir);
        Color indirect = trace(indirectRay, scene, maxDepth - 1);
        indirect = indirect / p;
        float cosTheta = std::max(normal.dot(newDir), 0.0f);
        Color brdf = closest_material.diffuseColor / PI;
        indirect_color = indirect * brdf * cosTheta;
    }

    return {direct_color + indirect_color,
            direct_color,
            indirect_color,
            shortest_distance,
            closest_id,
            normal};
}

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
