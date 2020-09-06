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
            double aspect_ratio,
            double aperture,
            double focus_dist
            ) 
        {
            auto theta = DegreesToRadians(vfov);
            auto h = tan(theta / 2);
            auto viewportHeight = 2.0 * h;
            auto viewportWidth = aspect_ratio * viewportHeight;

            m_W = UnitVector(lookfrom - lookat);
            m_U = UnitVector(Cross(vup, m_W));
            m_V = Cross(m_W, m_U);

            m_Origin = lookfrom;
            m_Horizontal = focus_dist * viewportWidth * m_U;
            m_Vertical = focus_dist * viewportHeight * m_V;
            m_LowerLeftCorner = m_Origin - m_Horizontal / 2 - m_Vertical / 2 - focus_dist * m_W;

            m_LensRadius = aperture / 2;
        }

        Ray GetRay(double s, double t) const
        {
            Vec3 rd = m_LensRadius * RandomInUnitDisk();
            Vec3 offset = m_U * rd.x() + m_V * rd.y();

            return Ray(
                m_Origin + offset,
                m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin - offset
            );
        }

    private:
        Point3 m_Origin;
        Point3 m_LowerLeftCorner;
        Vec3 m_Horizontal;
        Vec3 m_Vertical;
        Vec3 m_U, m_V, m_W;
        double m_LensRadius;
    };

}