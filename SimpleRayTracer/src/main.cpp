#include <iostream>

#include "util/ImageExporter.h"
#include "util/Vec3.h"
#include "util/Ray.h"

using namespace SimpleRayTracer;

bool hit_sphere(const Point3& center, double radius, const Ray& r) {
    Vec3 oc = r.Origin() - center;
    auto a = dot(r.Direction(), r.Direction());
    auto b = 2.0 * dot(oc, r.Direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

Color ray_color(const Ray& r) {
    if (hit_sphere(Point3(0, 0, -1), 0.5, r))
        return Color(1, 0, 0);

    Vec3 unit_direction = unit_vector(r.Direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);


    // Render
    auto imageExporter = std::make_unique<SimpleRayTracer::ImageExporter>(image_width, image_height, 3);

    int index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i) {

            auto u = double(i) / ((double)image_width - 1);
            auto v = double(j) / ((double)image_height - 1);

            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            Color pixel_color = ray_color(r);

            imageExporter->AddPixelColor(index, pixel_color);
            index += 3;
        }
    }
    std::cerr << "\nDone.\n";
  
    imageExporter->SaveAsPng("result.png");

    return 0;
}