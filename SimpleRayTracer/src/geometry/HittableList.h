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

    bool HittableList::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
    {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& object : m_Objects) {
            if (object->Hit(r, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.T;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
}