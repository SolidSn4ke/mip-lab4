#pragma once
#include "../math/color.h"
#include "../math/image.h"
#include "../math/rgb8.h"
#include "../math/trace.h"

/**
 * @brief Сервис для пост-процессинга изображения (фильтрация, тонирование).
 */
class PostProcessor {
  public:
    /**
     * @brief Применяет билатеральную фильтрацию и преобразует изображение в формат LDR.
     *
     * @param renderImage изображение с данными рендеринга.
     * @return Изображение в формате LDR.
     */
    static Image<RGB8> process(const Image<RenderPixel>& renderImage);
};
