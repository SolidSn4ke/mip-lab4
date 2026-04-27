#include "obj_service.h"
#include <fstream>
#include <iostream>
#include <sstream>

static int parseIndex(const std::string& token) {
    // Берём только часть до '/'
    size_t pos = token.find('/');
    if (pos == std::string::npos)
        return std::stoi(token);

    return std::stoi(token.substr(0, pos));
}

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
            std::string t1, t2, t3;
            ss >> t1 >> t2 >> t3;

            int i1 = parseIndex(t1);
            int i2 = parseIndex(t2);
            int i3 = parseIndex(t3);

            triangles.emplace_back(vertices[i1 - 1], vertices[i2 - 1], vertices[i3 - 1]);
        }
    }

    return triangles;
}