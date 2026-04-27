#include "obj_service.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<Triangle> OBJService::parse_obj(const std::string& filename) {
    std::vector<Vector> vertices;
    std::vector<Triangle> triangles;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << filename << std::endl;
        return triangles;
    }

    std::string line;

    while (std::getline(file, line)) {
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

            // OBJ индексы начинаются с 1
            triangles.emplace_back(vertices[i1 - 1], vertices[i2 - 1], vertices[i3 - 1]);
        }
    }

    return triangles;
}