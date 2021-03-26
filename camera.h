#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class camera {
    private:
        point3 origin;
        point3 bottom_left_corner;
        vec3 horizontal;
        vec3 vertical;
        const float aspect_ratio = 16.0 / 9.0;

    public:
        camera() {
            float viewport_height = 2.0;
            float viewport_width = viewport_height * aspect_ratio;
            float focal_length = 1.0;

            origin = point3(0, 0, 0);
            horizontal = vec3(viewport_width, 0, 0);
            vertical = vec3(0, viewport_height, 0);
            bottom_left_corner = origin 
                - (horizontal/2)            // x
                - (vertical/2)              // y
                - vec3(0, 0, focal_length); // z
        }

        ray get_ray(float u, float v) const {
            return ray(origin, bottom_left_corner + u*horizontal + v*vertical - origin);
        }
};

#endif
