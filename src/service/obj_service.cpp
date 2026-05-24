#include "obj_service.h"
#include <iostream>
#include <sstream>

std::vector<Triangle> OBJService::parse_obj(const std::string& obj_content) {
    std::vector<Vector> vertices;
    std::vector<Triangle> triangles;

    std::istringstream file(obj_content);

    std::string line;

    while (std::getline(file, line)) {

        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream ss(line);
        std::string type;
        ss >> type;

        // Вершины
        if (type == "v") {
            float x, y, z;
            ss >> x >> y >> z;

            vertices.emplace_back(x, y, z);
        }

        // Треугольники
        else if (type == "f") {
            int i1, i2, i3;
            ss >> i1 >> i2 >> i3;

            triangles.emplace_back(vertices[i1 - 1], vertices[i2 - 1], vertices[i3 - 1]);
        }
    }

    return triangles;
}