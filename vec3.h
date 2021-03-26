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

        float x() const {
            return e[0];
        }

        float y() const {
            return e[1];
        }

        float z() const {
            return e[2];
        }

        vec3 operator-() const {

        }

        float operator[](int i) const {

        }

        float& operator[](int i) {

        }

        vec3& operator+=(const vec3& v) {

        }

        vec3& operator*=(const vec3& v) {

        }

        vec3& operator/=(const vec3& v) {
            
        }

        float magnitude() const {

        }

        // square roots are expensive, don't use them if not necessary
        float sqr_magnitude() const {

        }
};
