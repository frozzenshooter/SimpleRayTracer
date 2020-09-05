#include "Sphere.h"

namespace SimpleRayTracer {

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
                return true;
            }

            temp = (-half_b + root) / a;
            if (temp < t_max && temp > t_min) {
                rec.T = temp;
                rec.Point = ray.At(rec.T);
                Vec3 outwardNormal = (rec.Point - m_Center) / m_Radius;
                rec.SetFaceNormal(ray, outwardNormal);
                return true;
            }
        }

        return false;
    }

}