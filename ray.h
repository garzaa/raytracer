#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    // public properties
    public:
        point3 o;
        vec3 d;

    //public methods
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction)
            : o(origin), d(direction)
        {}

        point3 origin() const { 
            return o;
        }

        vec3 direction() const {
            return d;
        }

        // P(t) = A + tb
        point3 at(float t) const {
            return o + t*d;
        }

};

#endif
