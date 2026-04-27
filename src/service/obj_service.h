#pragma once

#include "../math/triangle.h"
#include "../math/vector.h"
#include <string>
#include <vector>

class OBJService {

  public:
    static std::vector<Triangle> parse_obj(const std::string& obj_content);
};