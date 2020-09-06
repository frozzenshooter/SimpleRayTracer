#pragma once

#include <cmath>
#include <iostream>
#include "Core.h"

namespace SimpleRayTracer{

    class Vec3 {

    public:

        Vec3() 
            : e{ 0,0,0 } 
        {}

        Vec3(double e0, double e1, double e2) 
            : e{ e0, e1, e2 }
        {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vec3 operator-() const 
        { 
            return Vec3(-e[0], -e[1], -e[2]); 
        }

        double operator[](int i) const 
        {
            return e[i];
        }

        double& operator[](int i) 
        { 
            return e[i]; 
        }

        Vec3& operator+=(const Vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= 1 / t;
        }

        double Length() const {
            return std::sqrt(LengthSquared());
        }

        double LengthSquared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        inline static Vec3 Random() {
            return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
        }

        inline static Vec3 Random(double min, double max) {
            return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
        }

    public:
        double e[3];

    };

    // Type aliases for vec3
    using Point3 = Vec3;   // 3D point

    // vec3 Utility Functions

    inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    inline Vec3 operator+(const Vec3& u, const Vec3& v) {
        return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    inline Vec3 operator-(const Vec3& u, const Vec3& v) {
        return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    inline Vec3 operator*(const Vec3& u, const Vec3& v) {
        return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    inline Vec3 operator*(double t, const Vec3& v) {
        return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
    }

    inline Vec3 operator*(const Vec3& v, double t) {
        return t * v;
    }

    inline Vec3 operator/(Vec3 v, double t) {
        return (1 / t) * v;
    }

    inline double Dot(const Vec3& u, const Vec3& v) {
        return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
    }

    inline Vec3 Cross(const Vec3& u, const Vec3& v) {
        return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
            u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    inline Vec3 UnitVector(Vec3 v) {
        return v / v.Length();
    }

    Vec3 RandomInUnitSphere() {
        while (true) {
            auto p = Vec3::Random(-1, 1);
            if (p.LengthSquared() >= 1) continue;
            return p;
        }
    }

    Vec3 RandomUnitVector() {
        auto a = RandomDouble(0, 2 * pi);
        auto z = RandomDouble(-1, 1);
        auto r = sqrt(1 - z * z);
        return Vec3(r * cos(a), r * sin(a), z);
    }

    Vec3 RandomInHemisphere(const Vec3& normal) {
        Vec3 inUnitSphere = RandomInUnitSphere();
        if (Dot(inUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
            return inUnitSphere;
        else
            return -inUnitSphere;
    }

    Vec3 Reflect(const Vec3& v, const Vec3& n) {
        return v - 2 * Dot(v, n) * n;
    }
}