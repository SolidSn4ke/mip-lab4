#include "ppm_writer.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

std::string PPMWriter::generatePPM(const Image<RGB8>& image) {
    std::stringstream ss;
    ss << "P3\n";
    ss << image.width << " " << image.height << "\n";
    ss << "255\n";

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            const RGB8& color = image.getPixel(x, y);
            ss << color.r << " " << color.g << " " << color.b << "\n";
        }
    }

    return ss.str();
}

void PPMWriter::write(const std::string& ppmContent, const std::string& directory) {
    auto t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "render_%d-%m-%Y %H-%M-%S.ppm");

    std::ofstream out(directory + oss.str());

    if (!out.is_open()) {
        throw std::runtime_error("Cannot open directory: " + directory);
    }

    out << ppmContent;
}
