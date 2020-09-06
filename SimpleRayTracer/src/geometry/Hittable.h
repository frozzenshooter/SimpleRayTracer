#pragma once

#include "util/Ray.h"

namespace SimpleRayTracer {

    class Material;

    struct HitRecord {
        Point3 Point;
        Vec3 Normal;
        std::shared_ptr<Material> Material;
        double T = 0.00;
        bool FrontFace = false;

        inline void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
            FrontFace = Dot(ray.Direction(), outwardNormal) < 0;
            Normal = FrontFace ? outwardNormal : -outwardNormal;
        }
    };

    class Hittable {
    public:
        virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    };
}