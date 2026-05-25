#include "ppm_writer.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

std::string PPMWriter::generatePPM(const Image<RGB8>& image) {
    std::ostringstream ss;
    ss << "P3\n";
    ss << image.width << " " << image.height << "\n";
    ss << "255\n";

    int count = 0;

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            const RGB8& c = image.getPixel(x, y);

            ss << (int)c.r << " " << (int)c.g << " " << (int)c.b << " ";

            if (++count % 5 == 0)
                ss << "\n";
        }
    }

    ss << "\n";
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
