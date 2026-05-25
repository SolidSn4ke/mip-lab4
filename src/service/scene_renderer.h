#pragma once

#include "../math/camera.h"
#include "../math/color.h"
#include "../math/image.h"
#include "../math/scene.h"
#include <string>
#include <vector>

/**
 * @brief Высокоуровневый рендерер сцены в изображение.
 *
 * Отвечает за построение камеры, сцены и запуск процесса рендеринга.
 * Результат может быть сохранён в PPM файл или возвращён как строка.
 */
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

    /**
     * @brief Рендерит сцену и сохраняет результат в PPM файл.
     *
     * @param triangles Геометрия сцены (треугольники)
     * @param output_filename Имя выходного файла
     */
    void render(const std::vector<Triangle>& triangles, const std::string& output_filename);

    /**
     * @brief Рендерит сцену и возвращает результат в виде PPM строки.
     *
     * @param triangles Геометрия сцены (треугольники)
     * @return Строка в формате PPM (P3)
     */
    std::string renderToString(const std::vector<Triangle>& triangles);

  private:
    /**
     * @brief Создаёт камеру на основе параметров рендера.
     *
     * @return Сконфигурированная камера
     */
    Camera create_camera();

    /**
     * @brief Создаёт сцену из входных треугольников.
     *
     * @param triangles Геометрия сцены
     * @return Сцена для трассировки лучей
     */
    Scene create_scene(const std::vector<Triangle>& triangles);

    /**
     * @brief Рендерит сцену в HDR изображение.
     *
     * @param camera Камера
     * @param scene Сцена
     * @return HDR изображение (linear color space)
     */
    Image<Color> render_image(const Camera& camera, const Scene& scene);
};
