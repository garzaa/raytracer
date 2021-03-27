#ifndef TRACER_H
#define TRACER_H

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

#include "ray.h"
#include "vec3.h"

#endif
