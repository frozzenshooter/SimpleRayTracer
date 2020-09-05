#pragma once

#include "Hittable.h"

namespace SimpleRayTracer {

    class Sphere : public Hittable {
    public:
        Sphere()
            : m_Center({ 0.0f, 0.0f, 0.0f }), m_Radius(0.00)
        {}

        Sphere(Point3 center, double radius) : m_Center(center), m_Radius(radius) {};

        virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    public:
        Point3 m_Center;
        double m_Radius;

    };
}