#include <iostream>

#include "util/Color.h"
#include "util/ImageExporter.h"
#include "geometry/Sphere.h"
#include "geometry/HittableList.h"
#include "transforms\Camera.h"

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

Color RayColor(const Ray& r, const Hittable& world, int depth) {
    HitRecord rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0, 0, 0);

    if (world.Hit(r, 0.001, infinity, rec)) {
        Point3 target = rec.Point + rec.Normal + RandomUnitVector();
        return 0.5 * RayColor(Ray(rec.Point, target - rec.Point), world, --depth);
    }

    Vec3 unit_direction = UnitVector(r.Direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    Camera cam;


    // Render
    auto imageExporter = std::make_unique<SimpleRayTracer::ImageExporter>(image_width, image_height, 3);

    int index = 0;
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i) {

            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + RandomDouble()) / ((double)image_width - 1);
                auto v = (j + RandomDouble()) / ((double)image_height - 1);
                Ray r = cam.GetRay(u, v);
                pixel_color += RayColor(r, world, max_depth);
            }
            imageExporter->AddPixelColor(index, pixel_color, samples_per_pixel);
            index += 3;
        }
    }
    std::cerr << "\nDone.\n";
  
    imageExporter->SaveAsPng("result.png");

    return 0;
}