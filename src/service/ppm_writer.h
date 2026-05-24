#pragma once

#include "../math/image.h"
#include "../math/rgb8.h"
#include <string>

/**
 * @brief Сервис для конвертации изображения в формат PPM.
 */
class PPMWriter {
  public:
    /**
     * @brief Конвертирует изображение в формат PPM и возвращает содержимое в виде строки.
     *
     * @param image изображение для конвертации.
     * @return Строка в формате PPM.
     */
    static std::string generatePPM(const Image<RGB8>& image);

    /**
     * @brief Сохраняет PPM в указанную директорию.
     *
     * @param ppmContent содержимое PPM файла.
     * @param directory имя директории для сохранения.
     */
    static void write(const std::string& ppmContent, const std::string& directory);
};