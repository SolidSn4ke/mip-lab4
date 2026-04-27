#include "camera.h"
#include <cmath>

// Конструктор
Camera::Camera(const Vector& pos, const Vector& forward, const Vector& up, const Vector& right,
               float fov)
    : position(position), forward(forward), up(up), right(right), fov(fov) {}

Ray Camera::generate_ray(float x, float y, int w, int h) {
    float ndc_x = (x + 0.5f) / w;
    float ndc_y = (y + 0.5f) / h;

    float screen_x = 2.0f * ndc_x - 1.0f;
    float screen_y = 1.0f - 2.0f * ndc_y;

    float scale = std::tan(fov * 0.5f);

    Vector dir = forward + right * (screen_x * scale) + up * (screen_y * scale);

    dir = dir.normalize();

    return Ray(position, dir);
}