#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class camera {
    private:
        point3 origin;
        point3 bottom_left_corner;
        vec3 horizontal_size;
        vec3 vertical_size;
        float aspect_ratio;

    public:
        camera(float aspect) {
            aspect_ratio = aspect;

            float viewport_height = 2.0;
            float viewport_width = aspect_ratio * viewport_height;
            float focal_length = 1.0;
            
            origin = point3(0, 0, 0);
            horizontal_size = vec3(viewport_width, 0, 0);
            vertical_size = vec3(0, viewport_height, 0);
            bottom_left_corner = origin 
                - (horizontal_size/2)            // x
                - (vertical_size/2)              // y
                - vec3(0, 0, focal_length); // z
        }

        ray get_ray(float u, float v) const {
            return ray(origin, bottom_left_corner + u*horizontal_size + v*vertical_size - origin);
        }
};

#endif
