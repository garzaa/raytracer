#ifndef MATERIAL_H
#define MATERIAL_H

#include "tracer.h"

class material {
    public:
        color albedo;

    public:
        material(
            const color& a,
            const color& base,
            const 
        ) :
            albedo(a)
        {}

        bool scatter(
            const ray& in,
            const hit_record& hit,
            color& attenuation,
            ray& scattered
        ) {
            // lambertian
            vec3 scatter_direction = hit.normal * random_on_unit_sphere();

            // catch a zero scatter direction (sphere center plus inverse normal)
            if (scatter_direction.near_zero()) {
                scatter_direction = hit.normal;
            }

            scattered = ray(hit.point, scatter_direction);
            attenuation = albedo;
            return true;
        }
};

#endif
