#ifndef HITTABLE_H
#define HITTABLE_H

#include "tracer.h"

struct hit_record {
    point3 point;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    float distance;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
    public:
        virtual bool onhit(
            const ray& r,
            float min_distance,
            float max_distance,
            hit_record& hit
        ) const = 0;
};

#endif
