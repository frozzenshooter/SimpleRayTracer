#pragma once
#include "util/Core.h"

namespace SimpleRayTracer {

    class Camera {
    public:
        Camera(
            Point3 lookfrom,
            Point3 lookat,
            Vec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio
            ) 
        {
            auto theta = DegreesToRadians(vfov);
            auto h = tan(theta / 2);
            auto viewportHeight = 2.0 * h;
            auto viewportWidth = aspect_ratio * viewportHeight;

            auto w = UnitVector(lookfrom - lookat);
            auto u = UnitVector(Cross(vup, w));
            auto v = Cross(w, u);

            m_Origin = lookfrom;
            m_Horizontal = viewportWidth * u;
            m_Vertical = viewportHeight * v;
            m_LowerLeftCorner = m_Origin - m_Horizontal / 2 - m_Vertical / 2 - w;
        }

        Ray GetRay(double s, double t) const
        {
            return Ray(m_Origin, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin);
        }

    private:
        Point3 m_Origin;
        Point3 m_LowerLeftCorner;
        Vec3 m_Horizontal;
        Vec3 m_Vertical;
    };

}