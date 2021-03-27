#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "tracer.h"

class sphere : public hittable {
    public:
        point3 center;
        float radius;
        shared_ptr<material> mat_ptr;

    public:
        sphere() {}
        sphere(point3 c, float r, shared_ptr<material> m): 
            center(c), radius(r), mat_ptr(m) {};

        virtual bool onhit(
            const ray& r,
            float min_distance,
            float max_distance,
            hit_record& hit
        ) const override;
};

bool sphere::onhit(
            const ray& r,
            float min_distance,
            float max_distance,
            hit_record& hit
        ) const {

        // optimized quadratic code
        vec3 oc = r.origin() - center;
        float a = r.direction().sqr_magnitude();
        float half_b = dot(oc, r.direction());
        float c = oc.sqr_magnitude() - radius*radius;

        // check for collision at all
        float discriminant = half_b*half_b - a*c;            
        if (discriminant < 0) {
            return false;
        }

        // get nearest collision point if within distance
        float sqrtd = sqrt(discriminant);
        float root = (-half_b - sqrtd) / a;
        if (root < min_distance || root > max_distance) {
            root = (-half_b + sqrtd) / a;
            if (root < min_distance || root > max_distance) {
                return false;
            }
        }

        hit.distance = root;
        hit.point = r.at(hit.distance);
        vec3 outward_normal = (hit.point - center) / radius;
        hit.set_face_normal(r, outward_normal);
        hit.normal = (hit.point - center) / radius;
        hit.mat_ptr = mat_ptr;

        return true;

}
#endif
