#pragma once

#include "../math/camera.h"
#include "../math/image.h"
#include "../math/scene.h"
#include <string>
#include <vector>

class SceneRenderer {
  public:
    // Параметры рендеринга
    int width;
    int height;
    int samples_per_pixel;

    // Параметры сцены (заглушки для заполнения из формы)
    Vector camera_position;
    Vector camera_target;
    std::vector<LightSource> lights;
    std::vector<Vector> triangle_colors;

    SceneRenderer();

    // Отрендерить сцену и сохранить в PPM файл
    void render(const std::vector<Triangle>& triangles, const std::string& output_filename);

    // Отрендерить сцену и вернуть PPM как строку
    std::string renderToString(const std::vector<Triangle>& triangles);

  private:
    // Вспомогательные методы
    Camera create_camera();
    Scene create_scene(const std::vector<Triangle>& triangles);
    Image render_image(const Camera& camera, const Scene& scene);
};
