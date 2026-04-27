#include "camera.h"
#include <cmath>

// Конструктор
Camera::Camera(const Vector& pos, const Vector& forward, const Vector& up, const Vector& right,
               float fov)
    : position(pos), forward(forward), up(up), right(right), fov(fov) {}

Camera::Camera(const Vector& pos, const Vector& forward) : position(pos) {
    this->forward = forward.normalize();

    Vector worldUp(0, 1, 0);

    right = this->forward.cross(worldUp).normalize();
    up = right.cross(this->forward).normalize();
    fov = 1.01f;
}

Ray Camera::generate_ray(int x, int y, int w, int h) {
    float ndc_x = (x + 0.5f) / w;
    float ndc_y = (y + 0.5f) / h;

    float screen_x = 2.0f * ndc_x - 1.0f;
    float screen_y = 1.0f - 2.0f * ndc_y;

    float scale = std::tan(fov * 0.5f);

    Vector dir = forward + right * (screen_x * scale) + up * (screen_y * scale);

    dir = dir.normalize();

    return Ray(position, dir);
}