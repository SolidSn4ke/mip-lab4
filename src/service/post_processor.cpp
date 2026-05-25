#include "post_processor.h"
#include <cmath>

static uint8_t toByte(double v) {
    // защита от мусора (NaN / inf)
    if (!std::isfinite(v))
        return 0;

    // Tone mapping (Сжатие диапазона HDR в [0,1])
    v = v / (1.0 + v);

    // Gamma correction (Для корректного восприятия на мониторе)
    v = std::pow(v, 1.0 / 2.2);

    // Защита от переполнения
    v = (v < 0.0) ? 0.0 : (v > 1.0 ? 1.0 : v);

    // Перевод в [0,255] с округлением
    return static_cast<uint8_t>(v * 255.0 + 0.5);
}

Image<RGB8> PostProcessor::process(const Image<Color>& hdrImage) {
    Image<RGB8> result(hdrImage.width, hdrImage.height);

    for (int y = 0; y < hdrImage.height; y++) {
        for (int x = 0; x < hdrImage.width; x++) {
            const Color& c = hdrImage.getPixel(x, y);

            RGB8 pixel(toByte(c.r), toByte(c.g), toByte(c.b));

            result.setPixel(x, y, pixel);
        }
    }
    return result;
}