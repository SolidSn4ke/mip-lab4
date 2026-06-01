#include "post_processor.h"
#include <algorithm>
#include <cmath>
#include <iostream>

static uint8_t toByte(double v) {
    if (!std::isfinite(v))
        return 0;

    v = v / (1.0 + v);
    v = std::pow(v, 1.0 / 2.2);
    v = (v < 0.0) ? 0.0 : (v > 1.0 ? 1.0 : v);
    uint8_t result = (uint8_t)(v * 255.0 + 0.5);
    return result;
}

Image<RGB8> PostProcessor::process(const Image<RenderPixel>& renderImage) {
    int width = renderImage.width;
    int height = renderImage.height;
    Image<RGB8> result(width, height);

    const float sigma_s = 2.0f;
    const float sigma_d = 0.1f;
    const float sigma_n = 0.1f;
    const int radius = 5;

    float sum_prev = 0;
    float sum_after = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const RenderPixel& p = renderImage.getPixel(x, y);

            Color filtered_color(0, 0, 0);
            double total_weight = 0;

            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                        continue;

                    const RenderPixel& q = renderImage.getPixel(nx, ny);

                    // Preserve boundaries: if objects are different, weight is 0
                    if (p.objectId != q.objectId && p.objectId != -1 && q.objectId != -1) {
                        continue;
                    }

                    float dist_sq = (float)(dx * dx + dy * dy);
                    float spatial_weight = std::exp(-dist_sq / (2.0f * sigma_s * sigma_s));

                    float depth_diff = p.depth - q.depth;
                    float normal_diff = 1.0f - p.normal.dot(q.normal);
                    float range_weight =
                        std::exp(-(depth_diff * depth_diff / (2.0f * sigma_d * sigma_d) +
                                   normal_diff * normal_diff / (2.0f * sigma_n * sigma_n)));

                    float weight = spatial_weight * range_weight;
                    filtered_color = filtered_color + q.finalColor * weight;
                    total_weight += weight;
                }
            }

            Color final_hdr_color =
                (total_weight > 0) ? filtered_color * (1.0 / total_weight) : p.finalColor;

            // Y = 0.2126 * R_linear + 0.7152 * G_linear + 0.0722 * B_linear
            sum_prev += 0.2126 * final_hdr_color.r + 0.7152 * final_hdr_color.g +
                        0.0722 * final_hdr_color.b;
            sum_after +=
                0.2126 * p.finalColor.r + 0.7152 * p.finalColor.g + 0.0722 * p.finalColor.b;
            RGB8 pixel(toByte(final_hdr_color.r), toByte(final_hdr_color.g),
                       toByte(final_hdr_color.b));
            result.setPixel(x, y, pixel);
        }
    }
    std::cout << "Prev: " << sum_prev << "\n";
    std::cout << "After: " << sum_after << "\n";
    return result;
}
