#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
    // public properties
    public:
        float e[3];

    // public methods
    public:
        vec3(): e{0, 0, 0} {}
        vec3(float x, float y, float z): e{x, y, z} {}

        inline static vec3 random() {
            return vec3(randfloat(), randfloat(), randfloat());
        }

        inline static vec3 random(float min, float max) {
            return vec3(randrange(min, max), randrange(min, max), randrange(min, max));
        }

        float x() const {
            return e[0];
        }

        float y() const {
            return e[1];
        }

        float z() const {
            return e[2];
        }

        // don't want to write horrible code to support vector swizzling
        // so this is the next best thing for color structs without inheritance
        float r() const {
            return x();
        }

        float g() const {
            return y();
        }

        float b() const {
            return z();
        }

        vec3 operator-() const {
            return vec3(-e[0], -e[1], -e[2]);
        }

        float operator[](int i) const {
            return e[i];
        }

        float& operator[](int i) {
            return e[i];
        }

        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const float t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const float t) {
            return *this *= 1/t;
        }

        float magnitude() const {
            return sqrt(sqr_magnitude());
        }

        // square roots are expensive, don't use them if not necessary
        float sqr_magnitude() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        const float dot(const vec3 &v) {
            return e[0] * v[0]
                +  e[1] * v[1]
                +  e[2] * v[2];
        }

        const bool near_zero() {
            const float margin = 1e-8;
            return (fabs(e[0]) < margin) && (fabs(e[1]) < margin) && (fabs(e[2]) < margin);
        }
};

// type aliases
using point3 = vec3;
using color  = vec3;


// other utility functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(float t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, float t) {
    return t * v;
}

inline vec3 operator/(vec3 v, float t) {
    return (1/t) * v;
}

inline float dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
        +  u.e[1] * v.e[1]
        +  u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 normalize(vec3 v) {
    return v / v.magnitude();
}

inline vec3 random_on_unit_sphere() {
    return normalize(vec3::random());
}

inline vec3 lerp(vec3 a, vec3 b, float t) {
    return a + t*(b-a);
}

vec3 reflect(const vec3& i, const vec3& n) {
    return i - 2*n*dot(i, n);
}

#endif
