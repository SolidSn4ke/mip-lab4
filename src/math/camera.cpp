#include "camera.h"
#include <cmath>

#define PI 3.14f

Camera::Camera(const Vector& pos, const Vector& forward, const Vector& up, const Vector& right,
               float fov)
    : position(pos), forward(forward), up(up), right(right), fov(fov) {}

Ray Camera::generate_ray(int x, int y, int w, int h) const {
    // Перевод координат центра пикселя из [0,w], [0,h] в диапазон [0.1]
    float ndc_x = (x + 0.5f) / w;
    float ndc_y = (y + 0.5f) / h;

    // Перевод координат из диапазона [0 .. 1]
    // в координаты виртуального экрана [-1 .. 1].
    //
    // screen_x:
    // -1 = левый край экрана
    //  0 = центр
    // +1 = правый край
    //
    // screen_y инвертируется потому что:
    // в изображении Y растёт вниз,
    // а в 3D пространстве обычно вверх.
    float screen_x = 2.0f * ndc_x - 1.0f;
    float screen_y = 1.0f - 2.0f * ndc_y;

    // Масштаб виртуального экрана.
    //
    // FOV задаёт угол обзора камеры.
    // Чем больше FOV:
    // - тем шире угол обзора
    //
    // tan(fov / 2) вычисляет половину
    // размера виртуального экрана
    // на расстоянии 1 от камеры.
    //
    // PI / 180 нужен для перевода градусов в радианы.
    float scale = std::tan(fov * 0.5f * PI / 180.0f);

    // Строим направление луча.
    //
    // forward -> центр экрана
    // right   -> смещение по X
    // up      -> смещение по Y
    Vector dir = forward + right * (screen_x * scale) + up * (screen_y * scale);

    // Нормализуем направление,
    // чтобы длина вектора была равна 1.
    //
    // Для трассировки важна только
    // ориентация луча, а не его длина.
    dir = dir.normalize();

    // Создаём луч:
    // origin    -> позиция камеры
    // direction -> направление через пиксель
    return Ray(position, dir);
}