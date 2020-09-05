#pragma once

#include <string>
#include "Color.h"

namespace SimpleRayTracer {

    class ImageExporter {
    public:
        ImageExporter(unsigned int width, unsigned int height, unsigned int channelCount);
        ~ImageExporter();

        int AddPixelColor(unsigned int index, Color color);

        int SaveAsPng(const char* filename);


    private:
        unsigned int m_Width;
        unsigned int m_Height;
        unsigned int m_ChannelCount;
        unsigned int m_Size;
        unsigned char* m_Data;
    };

}