#include <iostream>


#include "util/ImageExporter.h"

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;
    const int channel_count = 3;

    // Render
    auto imageExporter = std::make_unique<SimpleRayTracer::ImageExporter>(image_width, image_height, 3);

    int index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {

            auto rval = double(i) / ((double)image_width - 1);
            auto gval = double(j) / ((double)image_height - 1);
            auto bval = 0.25;

            SimpleRayTracer::Color pixel_color(rval, gval, bval);

            imageExporter->AddPixelColor(index, pixel_color);
            index += 3;
        }
    }
    std::cerr << "\nDone.\n";
  
    imageExporter->SaveAsPng("result.png");

    return 0;
}