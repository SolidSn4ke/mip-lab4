#include "post_processor.h"
#include <cmath>

static uint8_t toByte(double v) {
    // защита от мусора (NaN / inf)
    if (!std::isfinite(v))
        return 0;

    // tone mapping (Reinhard)
    v = v / (1.0 + v);

    // gamma correction (approx 2.2)
    v = std::pow(v, 1.0 / 2.2);

    v = (v < 0.0) ? 0.0 : (v > 1.0 ? 1.0 : v);

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