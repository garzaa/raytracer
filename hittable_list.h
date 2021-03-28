#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "tracer.h"
#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
    public:
        hittable_list() {}
        // bundle the instances together in memory
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool onhit(
            const ray& r, float min_distance, float max_distance, hit_record& hit) const override;

    public:
        std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::onhit(const ray& r, float min_distance, float max_distance, hit_record& hit) const {
    hit_record temp_hit;
    bool hit_anything = false;
    auto closest_so_far = max_distance;

    for (const auto& object : objects) {
        if (object->onhit(r, min_distance, closest_so_far, temp_hit)) {
            hit_anything = true;
            closest_so_far = temp_hit.distance;
            hit = temp_hit;
        }
    }

    return hit_anything;
}

#endif
