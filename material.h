#ifndef MATERIAL_H
#define MATERIAL_H

#include "tracer.h"

struct hit_record;

class material {
    public:
        virtual bool scatter(
            const ray& in,
            const hit_record& hit,
            color& attenuation,
            ray& scattered
        ) const = 0;
};

class lambertian : public material {
    public:
        color albedo;

    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        virtual bool scatter(
            const ray& in,
            const hit_record& hit,
            color& attenuation,
            ray& scattered
        ) const override {
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

class specular : public material {
    public:
        color albedo;

    public:
        specular(const color& albedo) : albedo(albedo) {}

        virtual bool scatter(
            const ray& in,
            const hit_record& hit,
            color& attenuation,
            ray& scattered
        ) const override {
            vec3 r = reflect(normalize(in.direction()), hit.normal);
            scattered = ray(hit.point, r);
            attenuation = albedo;
            return dot(scattered.direction(), hit.normal) > 0;
        }
};

#endif
