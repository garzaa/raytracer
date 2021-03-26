#include "camera.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

color bottom = color(1.0, 1.0, 1.0);
color top    = color(0.5, 0.7, 1.0);

color default_ray_color(const ray& r) {
    vec3 unit_direction = normalize(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return lerp(bottom, top, t);
}

int main() {

    // 1600x900 / 4
    const float aspect_ratio = 16.0 / 9.0;
    const int width = 900;
    const int height = static_cast<int>(width / aspect_ratio);

    camera cam = camera(aspect_ratio);

    // header: image params
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    // the original had a prefix increment for some reason
    for (int j = height-1; j >= 0; j--) {
        std::cerr << "\r" << j << " lines left" << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            // u and v are the coordinates inside the image, starting at the bottom left
            float u = float(i) / (width-1);
            float v = float(j) / (height-1);

            color pixel = default_ray_color(cam.get_ray(u, v));
            
            write_color(std::cout, pixel);
        }
    }
}
