#pragma once

#include "util/Ray.h"

namespace SimpleRayTracer {

    struct HitRecord {
        Point3 Point;
        Vec3 Normal;
        double T;
    };

    class Hittable {
    public:
        virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    };
}