#include <iostream>

#include "util/ImageExporter.h"
#include "util/Vec3.h"
#include "util/Ray.h"

using namespace SimpleRayTracer;

double HitSphere(const Point3& center, double radius, const Ray& ray) {
    Vec3 oc = ray.Origin() - center;
    auto a = ray.Direction().LengthSquared();
    auto half_b = Dot(oc, ray.Direction());
    auto c = oc.LengthSquared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

Color RayColor(const Ray& ray) {
    auto t = HitSphere(Point3(0, 0, -1), 0.5, ray);

    if (t > 0.0) {
        Vec3 normal = UnitVector(ray.At(t) - Point3(0, 0, -1));
        return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    Vec3 unit_direction = UnitVector(ray.Direction());

    t = 0.5 * (unit_direction.y() + 1.0);
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
            Color pixel_color = RayColor(r);

            imageExporter->AddPixelColor(index, pixel_color);
            index += 3;
        }
    }
    std::cerr << "\nDone.\n";
  
    imageExporter->SaveAsPng("result.png");

    return 0;
}