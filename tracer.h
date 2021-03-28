#ifndef TRACER_H
#define TRACER_H

#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float infinity = std::numeric_limits<float>::infinity();
const double pi = 3.1415926535897932385;

inline double deg2rad(float degrees) {
    return degrees * pi / 180.0;
}

inline float randfloat() {
    return rand() / (RAND_MAX + 1.0);
}

inline float randrange(float min, float max) {
    return min + (max-min) * randfloat();
}

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;

}

inline float saturate(float x) {
    return clamp(x, 0, 1);
}

#include "ray.h"
#include "vec3.h"

color bottom = color(1.0, 1.0, 1.0);
color top    = color(0.5, 0.7, 1.0);
color red    = color(1.0, 0.0, 0.0);
color white  = color(1.0, 1.0, 1.0);
color black  = color(0.0, 0.0, 0.0);

#endif
