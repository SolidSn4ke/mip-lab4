#pragma once

#include "../math/image.h"
#include <string>

class PPMWriter {
  public:
    static void write(const Image& image, const std::string& filename);
};