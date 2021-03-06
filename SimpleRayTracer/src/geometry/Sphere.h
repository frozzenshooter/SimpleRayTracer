#pragma once

#include "Hittable.h"

namespace SimpleRayTracer {

    class Sphere : public Hittable {
    public:
        Sphere()
            : m_Center({ 0.0f, 0.0f, 0.0f }), m_Radius(0.00), m_Material(nullptr)
        {}

        Sphere(Point3 center, double radius, std::shared_ptr<Material> material) : m_Center(center), m_Radius(radius), m_Material(material) 
        {}

        virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    public:
        Point3 m_Center;
        double m_Radius;
        std::shared_ptr<Material> m_Material;
    };

    bool Sphere::Hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const
    {
        Vec3 oc = ray.Origin() - m_Center;
        auto a = ray.Direction().LengthSquared();
        auto half_b = Dot(oc, ray.Direction());
        auto c = oc.LengthSquared() - m_Radius * m_Radius;
        auto discriminant = half_b * half_b - a * c;

        if (discriminant > 0) {
            auto root = sqrt(discriminant);

            auto temp = (-half_b - root) / a;
            if (temp < t_max && temp > t_min) {
                rec.T = temp;
                rec.Point = ray.At(rec.T);
                Vec3 outwardNormal = (rec.Point - m_Center) / m_Radius;
                rec.SetFaceNormal(ray, outwardNormal);
                rec.Material = m_Material;
                return true;
            }

            temp = (-half_b + root) / a;
            if (temp < t_max && temp > t_min) {
                rec.T = temp;
                rec.Point = ray.At(rec.T);
                Vec3 outwardNormal = (rec.Point - m_Center) / m_Radius;
                rec.SetFaceNormal(ray, outwardNormal);
                rec.Material = m_Material;
                return true;
            }
        }

        return false;
    }
}