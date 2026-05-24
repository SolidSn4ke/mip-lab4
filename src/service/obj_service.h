#pragma once

#include "../math/triangle.h"
#include "../math/vector.h"
#include <string>
#include <vector>

/**
 * @brief Сервис для парсинга OBJ файлов.
 */
class OBJService {
  public:
    /**
     * @brief Конвертирует содержимое OBJ файла в массив треугольников.
     *
     * Поддерживаются:
     * - вершины (`v`)
     * - треугольные полигоны (`f`)
     *
     * Не поддерживаются:
     * - нормали (`vn`)
     * - текстурные координаты (`vt`)
     * - полигоны более чем с 3 вершинами
     *
     * @param obj_content Содержимое OBJ файла.
     * @return Массив треугольников.
     */
    static std::vector<Triangle> parse_obj(const std::string& obj_content);
};