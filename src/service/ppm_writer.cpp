#include "ppm_writer.h"
#include <algorithm>
#include <fstream>

static int to255(float v) {
    return std::clamp(int(v * 255.0f), 0, 255);
}

void PPMWriter::write(const Image& image, const std::string& filename) {
    std::ofstream out(filename);

    if (!out.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    out << "P3\n";
    out << image.width << " " << image.height << "\n";
    out << "255\n";

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {

            const Color& c = image.pixels[y * image.width + x];

            int r = to255(c.r);
            int g = to255(c.g);
            int b = to255(c.b);

            out << r << " " << g << " " << b << "\n";
        }
    }
}