#include <iostream>

#include "util/Color.h"
#include "util/ImageExporter.h"
#include "geometry/Sphere.h"
#include "geometry/HittableList.h"
#include "transforms\Camera.h"
#include "geometry/Material.h"

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
        Ray scattered;
        Color attenuation;

        if (rec.Material->Scatter(r, rec, attenuation, scattered))
            return attenuation * RayColor(scattered, world, depth - 1);

        return Color(0, 0, 0);
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
    auto R = cos(pi / 4);
    HittableList world;

    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<Dielectric>(1.5);
    auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.45, material_left));
    world.Add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera
    Point3 lookfrom(3, 3, 2);
    Point3 lookat(0, 0, -1);
    Vec3 vup(0, 1, 0);
    auto dist_to_focus = (lookfrom - lookat).Length();
    auto aperture = 2.0;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

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