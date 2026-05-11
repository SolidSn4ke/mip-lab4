#include "ppm_writer.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

static int to255(float v) {
    int x = int(v * 255.0f);

    if (x < 0)
        return 0;
    if (x > 255)
        return 255;

    return x;
}

static std::string generatePPM(const Image& image) {
    std::stringstream ss;
    ss << "P3\n";
    ss << image.width << " " << image.height << "\n";
    ss << "255\n";

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            const Color& c = image.pixels[y * image.width + x];
            int r = to255(c.r);
            int g = to255(c.g);
            int b = to255(c.b);
            ss << r << " " << g << " " << b << "\n";
        }
    }
    return ss.str();
}

void PPMWriter::write(const Image& image, const std::string& filename) {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "render_%d-%m-%Y %H-%M-%S.ppm");

    std::ofstream out(filename + oss.str());

    if (!out.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    out << generatePPM(image);
}

std::string PPMWriter::writeToString(const Image& image) {
    return generatePPM(image);
}
