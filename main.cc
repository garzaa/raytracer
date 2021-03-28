#include "tracer.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

#include <iostream>

color color_normal(vec3 n) {
    // map (-1, 1) to (0, 1)
    return 0.5 * color(n.x()+1, n.y()+1, n.z()+1);
}

float hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = r.direction().sqr_magnitude();
    float half_b = dot(oc, r.direction());
    float c = oc.sqr_magnitude() - radius*radius;
    float discriminant = half_b*half_b - a*c;
    // > 0 means two roots
    // = 0 means one root
    // < 0 means pain if you're in middle school
    if (discriminant < 0) {
        return -1;
    } else {
        // return the nearest hit
        return (-half_b - sqrt(discriminant)) / a;
    }
}

color ray_color(const ray& r, const hittable& world, int bounces) {
    if (bounces <= 0) {
        return black;
    }

    hit_record hit;
    if (world.onhit(r, 0.001, infinity, hit)) {
        ray scattered;
        color attenuation;

        if (hit.mat_ptr->scatter(r, hit, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, bounces-1);
        }

        return black;
    }

    vec3 unit_direction = normalize(r.direction());
    // normalize the y-dir back to image uv-space
    float distance = 0.5 * (unit_direction.y() + 1.0);
    return lerp(bottom, top, distance);
}

int main() {

    const float aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int max_bounces = 10;
    const int aa_samples = 2;
    const int height = static_cast<int>(width / aspect_ratio);

    camera cam = camera(aspect_ratio);

    hittable_list world;

    auto ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto left   = make_shared<specular>(color(0.8, 0.8, 0.8));
    auto right  = make_shared<specular>(color(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, right));

    // header: image params
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height-1; j >= 0; j--) {
        std::cerr << "\r" << j << " lines left" << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            color pixel = color(0, 0, 0);
            
            for (int s=0; s<aa_samples; s++) {
                // u and v are the coordinates inside the image, starting at the bottom left
                float u = (i + randfloat()) / (width-1);
                float v = (j + randfloat()) / (height-1);
                ray r = cam.get_ray(u, v);
                pixel += ray_color(r, world, max_bounces);
            }
            
            write_color(std::cout, pixel, aa_samples);
        }
    }
}
