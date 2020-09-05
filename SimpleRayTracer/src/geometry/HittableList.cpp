#include "HittableList.h"

namespace SimpleRayTracer {

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