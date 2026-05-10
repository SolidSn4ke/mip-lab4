#include "scene_renderer.h"
#include "../math/trace.h"
#include "ppm_writer.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

SceneRenderer::SceneRenderer() {
    // Инициализировать генератор случайных чисел
    srand(time(nullptr));
}

Camera SceneRenderer::create_camera() {
    Vector look_direction = (camera_target - camera_position).normalize();
    return Camera(camera_position, look_direction);
}

Scene SceneRenderer::create_scene(const std::vector<Triangle>& triangles) {
    return Scene(triangles, lights);
}

Image SceneRenderer::render_image(const Camera& camera, const Scene& scene) {
    Image image(width, height);

    std::cout << "Rendering " << width << "x" << height << " with " << samples_per_pixel
              << " samples per pixel..." << std::endl;

    for (int y = 0; y < height; y++) {
        if (y % 100 == 0) {
            std::cout << "Progress: " << y << "/" << height << std::endl;
        }

        for (int x = 0; x < width; x++) {
            Color accumulated_color(0, 0, 0);

            // Антиалиасинг: несколько лучей на пиксель
            for (int s = 0; s < samples_per_pixel; s++) {
                // Случайное смещение в пределах пикселя
                float offset_x = (rand() / (float)RAND_MAX);
                float offset_y = (rand() / (float)RAND_MAX);

                Ray ray = camera.generate_ray(x + offset_x, y + offset_y, width, height);
                Color sample_color = trace(ray, scene);
                accumulated_color = accumulated_color + sample_color;
            }

            // Усредняем цвет
            Color final_color = accumulated_color * (1.0f / samples_per_pixel);

            // Гамма коррекция (gamma = 2.2)
            float gamma = 2.2f;
            final_color =
                Color(std::pow(final_color.r, 1.0f / gamma), std::pow(final_color.g, 1.0f / gamma),
                      std::pow(final_color.b, 1.0f / gamma));

            image.setPixel(x, y, final_color);
        }
    }

    std::cout << "Rendering complete!" << std::endl;
    return image;
}

std::string SceneRenderer::renderToString(const std::vector<Triangle>& triangles) {
    Camera camera = create_camera();
    Scene scene = create_scene(triangles);
    Image image = render_image(camera, scene);
    PPMWriter::write(image, "./out/");
    return PPMWriter::writeToString(image);
}
