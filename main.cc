#include "camera.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

color bottom = color(1.0, 1.0, 1.0);
color top    = color(0.5, 0.7, 1.0);
color red    = color(1.0, 0.0, 0.0);

color color_normal(vec3 n) {
    return 0.5*color(n.x()+1, n.y()+1, n.z()+1);
}

float hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    // > 0 means two roots
    // = 0 means one root
    // < 0 means pain if you're in middle school
    if (discriminant < 0) {
        return -1;
    } else {
        // return the nearest hit
        return (-b - sqrt(discriminant)) / (a * 2.0);
    }
}

color ray_color(const ray& r) {
    float t = hit_sphere(point3(0, 0, -1), 0.5, r);
    
    if (t > 0) {
        vec3 normal = normalize(r.at(t) + vec3(0, 0, 1));
        return color_normal(normal);
    }

    vec3 unit_direction = normalize(r.direction());
    // normalize the y-dir back to image uv-space
    t = 0.5 * (unit_direction.y() + 1.0);
    return lerp(bottom, top, t);
}

int main() {

    // 1600x900 / 4
    const float aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int height = static_cast<int>(width / aspect_ratio);

    camera cam = camera(aspect_ratio);

    // header: image params
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height-1; j >= 0; j--) {
        std::cerr << "\r" << j << " lines left" << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            // u and v are the coordinates inside the image, starting at the bottom left
            float u = float(i) / (width-1);
            float v = float(j) / (height-1);

            ray r = cam.get_ray(u, v);
            color pixel = ray_color(r);
            
            write_color(std::cout, pixel);
        }
    }
}
