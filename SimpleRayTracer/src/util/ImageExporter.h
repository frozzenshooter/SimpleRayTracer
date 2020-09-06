#pragma once

#include <string>
#include "Color.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace SimpleRayTracer {

    class ImageExporter {
    public:
        ImageExporter(unsigned int width, unsigned int height, unsigned int channelCount);
        ~ImageExporter();

        int AddPixelColor(unsigned int index, Color color, unsigned int samplesPerPixel);

        int SaveAsPng(const char* filename);


    private:
        unsigned int m_Width;
        unsigned int m_Height;
        unsigned int m_ChannelCount;
        unsigned int m_Size;
        unsigned char* m_Data;
    };

    ImageExporter::ImageExporter(unsigned int width, unsigned int height, unsigned int channelCount)
        : m_Width(width), m_Height(height), m_ChannelCount(channelCount), m_Size(height* width* channelCount), m_Data(new unsigned char[m_Size])
    {

    }

    ImageExporter::~ImageExporter() {
        delete[] m_Data;
    }

    int ImageExporter::AddPixelColor(unsigned int index, Color color, unsigned int samplesPerPixel)
    {
        if ((index + 2) > m_Size) {
            // only inside the set images size possible
            return -1;
        }

        auto r = color.x();
        auto g = color.y();
        auto b = color.z();

        // Divide the color by the number of samples and gamma-correct for gamma=2.0.
        auto scale = 1.0 / samplesPerPixel;
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);

        m_Data[index] = static_cast<unsigned char>(256 * Clamp(r, 0.0, 0.999));
        m_Data[index + 1] = static_cast<unsigned char>(256 * Clamp(g, 0.0, 0.999));
        m_Data[index + 2] = static_cast<unsigned char>(256 * Clamp(b, 0.0, 0.999));

        return 1;
    }

    int ImageExporter::SaveAsPng(const char* filename)
    {
        return stbi_write_png(filename, m_Width, m_Height, m_ChannelCount, m_Data, m_Width * m_ChannelCount);
    }

}