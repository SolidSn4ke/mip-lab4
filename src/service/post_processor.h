#pragma once
#include "../math/color.h"
#include "../math/image.h"
#include "../math/rgb8.h"

/**
 * @brief Сервис для преобразования изображения из формата HDR в формат LDR.
 */
class PostProcessor {
  public:
    /**
     * @brief Преобразует изображение из формата HDR в формат LDR.
     *
     * @param hdrImage изображение в формате HDR.
     * @return Изображение в формате LDR.
     */
    static Image<RGB8> process(const Image<Color>& hdrImage);
};
