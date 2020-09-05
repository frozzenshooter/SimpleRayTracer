#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

namespace SimpleRayTracer {

    class HittableList : public Hittable 
    {
    public:
        HittableList() {}
        HittableList(std::shared_ptr<Hittable> object)
        { 
            Add(object); 
        }

        void Clear() 
        { 
            m_Objects.clear(); 
        }

        void Add(std::shared_ptr<Hittable> object) {
            m_Objects.push_back(object);
        }

        virtual bool Hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const override;

    public:
        std::vector<std::shared_ptr<Hittable>> m_Objects;
    };
}