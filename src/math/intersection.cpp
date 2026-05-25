#include "intersection.h"
#include <cmath>

bool intersectTriangle(const Ray& ray, const Triangle& tri, HitInfo& hit) {

    const float EPS = 1e-6f; // Погрешность

    // Из одной вершины строим два вектора.
    Vector v0v1 = tri.v1 - tri.v0;
    Vector v0v2 = tri.v2 - tri.v0;

    // Вектор, перпендикулярный:
    // ray.direction и v0v2.
    //
    // Используется для вычисления
    // определителя системы.
    Vector pvec = ray.direction.cross(v0v2);

    // Определитель.
    //
    // Показывает:
    // - параллелен ли луч треугольнику
    // - с какой стороны происходит пересечение
    float det = v0v1.dot(pvec);

    // Если determinant близок к 0:
    // луч параллелен плоскости треугольника.
    if (fabs(det) < EPS) {
        return false;
    }

    // Обратное значение к determinant
    float invDet = 1.0f / det;

    // Вектор от вершины треугольника
    // к началу луча.
    Vector tvec = ray.origin - tri.v0;

    // Барицентрическая координата U.
    //
    // Показывает положение точки
    // внутри треугольника.
    float u = tvec.dot(pvec) * invDet;

    // Если u вне диапазона [0,1],
    // точка находится вне треугольника.
    if (u < 0 || u > 1) {
        return false;
    }

    // Вектор, перпендикулярный:
    // tvec и v0v1.
    Vector qvec = tvec.cross(v0v1);

    // Барицентрическая координата V.
    float v = ray.direction.dot(qvec) * invDet;

    // Проверяем:
    // - v должен быть >= 0
    // - u + v <= 1
    //
    // Иначе точка лежит вне треугольника.
    if (v < 0 || u + v > 1) {
        return false;
    }

    // Расстояние вдоль луча
    // до точки пересечения.
    //
    // ray.position = origin + direction * t
    float t = v0v2.dot(qvec) * invDet;

    // Если t < 0:
    // пересечение находится позади камеры.
    if (t < EPS) {
        return false;
    }

    // Сохраняем расстояние до точки.
    hit.t = t;

    // Вычисляем мировую позицию точки пересечения.
    hit.position = ray.origin + ray.direction * t;

    // Нормаль треугольника.
    //
    // cross(edge1, edge2)
    // даёт вектор, перпендикулярный поверхности.
    hit.normal = v0v1.cross(v0v2).normalize();

    return true;
}