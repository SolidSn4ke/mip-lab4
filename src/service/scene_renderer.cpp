#include "scene_renderer.h"
#include "../math/trace.h"
#include "post_processor.h"
#include "ppm_writer.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

SceneRenderer::SceneRenderer() {
    srand(time(nullptr));
}

Camera SceneRenderer::create_camera() {
    Vector look_direction = (camera_target - camera_position).normalize();

    // мировой "верх"
    Vector world_up(0.0f, 1.0f, 0.0f);

    // правая ось камеры
    Vector right = look_direction.cross(world_up).normalize();

    // реальный up камеры (ортогонализированный)
    Vector up = right.cross(look_direction).normalize();

    float fov = 60.0f;

    return Camera(camera_position, look_direction, up, right, fov);
}

Scene SceneRenderer::create_scene(const std::vector<Triangle>& triangles) {
    return Scene(triangles, lights);
}

Image<RenderPixel> SceneRenderer::render_image(const Camera& camera, const Scene& scene) {
    Image<RenderPixel> image(width, height);

    std::cout << "Rendering " << width << "x" << height << " with " << samples_per_pixel
              << " samples per pixel..." << std::endl;

    for (int y = 0; y < height; y++) {
        if (y % 100 == 0) {
            std::cout << "Progress: " << y << "/" << height << std::endl;
        }

        for (int x = 0; x < width; x++) {
            RenderPixel accumulated_pixel{Color(0,0,0), Color(0,0,0), Color(0,0,0), 0.0f, -1, Vector(0,0,0)};

            // Антиалиасинг: несколько лучей на пиксель
            for (int s = 0; s < samples_per_pixel; s++) {
                // Случайное смещение в пределах пикселя
                float offset_x = (rand() / (float)RAND_MAX);
                float offset_y = (rand() / (float)RAND_MAX);

                Ray ray = camera.generate_ray(x + offset_x, y + offset_y, width, height);
                RenderPixel sample = trace_first_hit(ray, scene, 4);

                accumulated_pixel.finalColor = accumulated_pixel.finalColor + sample.finalColor;
                accumulated_pixel.directColor = accumulated_pixel.directColor + sample.directColor;
                accumulated_pixel.indirectColor = accumulated_pixel.indirectColor + sample.indirectColor;
                accumulated_pixel.depth += sample.depth;
                // For objectId and normal, we'll take the one from the first sample of the pixel (or average, but usually first hit is representative)
                if (s == 0) {
                    accumulated_pixel.objectId = sample.objectId;
                    accumulated_pixel.normal = sample.normal;
                }
            }

            float invS = 1.0f / samples_per_pixel;
            accumulated_pixel.finalColor = accumulated_pixel.finalColor * invS;
            accumulated_pixel.directColor = accumulated_pixel.directColor * invS;
            accumulated_pixel.indirectColor = accumulated_pixel.indirectColor * invS;
            accumulated_pixel.depth *= invS;

            image.setPixel(x, y, accumulated_pixel);
        }
    }

    std::cout << "Rendering complete!" << std::endl;
    return image;
}

std::string SceneRenderer::renderToString(const std::vector<Triangle>& triangles) {
    Camera camera = create_camera();
    Scene scene = create_scene(triangles);
    Image<RenderPixel> renderImage = render_image(camera, scene);
    Image<RGB8> ldrImage = PostProcessor::process(renderImage);
    std::string ppmContent = PPMWriter::generatePPM(ldrImage);
    PPMWriter::write(ppmContent, "./out/");
    return ppmContent;
}
