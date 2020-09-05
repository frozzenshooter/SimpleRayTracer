#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;
    #define CHANNEL_NUM 3

    // Render

    auto size = image_width * image_height * 3;

    unsigned char* data = new unsigned char[size];

    int index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {

            auto r = double(i) / ((double)image_width - 1);
            auto g = double(j) / ((double)image_height - 1);
            auto b = 0.25;

            int ir = static_cast<unsigned char>(255.999 * r);
            int ig = static_cast<unsigned char>(255.999 * g);
            int ib = static_cast<unsigned char>(255.999 * b);

            data[index++] = ir;
            data[index++] = ig;
            data[index++] = ib;
        }
    }

    stbi_write_png("result.png", image_width, image_height, CHANNEL_NUM, data, image_width * CHANNEL_NUM);

    delete [] data;
    return 0;
}