#pragma once

#include "util/Ray.h";
#include "util/Color.h";

namespace SimpleRayTracer {

    struct HitRecord;

    class Material {
    public:
        virtual bool Scatter(const Ray& ray_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
    };

    class Lambertian : public Material {
    public:
        Lambertian(const Color& a) : m_Albedo(a) {}

        virtual bool Scatter(const Ray& ray_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override
        {
            Vec3 scatter_direction = rec.Normal + RandomUnitVector();
            scattered = Ray(rec.Point, scatter_direction);
            attenuation = m_Albedo;
            return true;
        }

    public:
        Color m_Albedo;
    };

    class Metal : public Material {
    public:
        Metal(const Color& a, double f) : m_Albedo(a), m_Fuzz(f < 1 ? f : 1) {}

        virtual bool Scatter(const Ray& ray_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override
        {
            Vec3 reflected = Reflect(UnitVector(ray_in.Direction()), rec.Normal);
            scattered = Ray(rec.Point, reflected + m_Fuzz * RandomInUnitSphere());
            attenuation = m_Albedo;
            return (Dot(scattered.Direction(), rec.Normal) > 0);
        }

    public:
        Color m_Albedo;
        double m_Fuzz;
    };

    class Dielectric : public Material {
    public:
        Dielectric(double ri) : ref_idx(ri) {}

        virtual bool Scatter(const Ray& ray_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override
        {
            attenuation = Color(1.0, 1.0, 1.0);
            double etai_over_etat = rec.FrontFace ? (1.0 / ref_idx) : ref_idx;

            Vec3 unit_direction = UnitVector(ray_in.Direction());

            double cos_theta = fmin(Dot(-unit_direction, rec.Normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
            if (etai_over_etat * sin_theta > 1.0) {
                Vec3 reflected = Reflect(unit_direction, rec.Normal);
                scattered = Ray(rec.Point, reflected);
                return true;
            }

            Vec3 refracted = Refract(unit_direction, rec.Normal, etai_over_etat);
            scattered = Ray(rec.Point, refracted);
            return true;
        }

        double ref_idx;
    };
}