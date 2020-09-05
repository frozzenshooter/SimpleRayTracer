#include "ImageExporter.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace SimpleRayTracer {


    ImageExporter::ImageExporter(unsigned int width, unsigned int height, unsigned int channelCount)
        : m_Width(width), m_Height(height), m_ChannelCount(channelCount), m_Size(height* width* channelCount), m_Data(new unsigned char[m_Size])
    {

    }

    ImageExporter::~ImageExporter() {
        delete[] m_Data;
    }

    int ImageExporter::AddPixelColor(unsigned int index, Color color)
    {
        if ((index + 2) > m_Size) {
            // only inside the set images size possible
            return -1;
        }

        m_Data[index] = static_cast<unsigned char>(255.999 * color.x());
        m_Data[index + 1] = static_cast<unsigned char>(255.999 * color.y());
        m_Data[index + 2] = static_cast<unsigned char>(255.999 * color.z());

        return 1;
    }

    int ImageExporter::SaveAsPng(const char* filename)
    {
        return stbi_write_png(filename, m_Width, m_Height, m_ChannelCount, m_Data, m_Width * m_ChannelCount);        
    }
}