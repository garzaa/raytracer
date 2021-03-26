#include "color.h"
#include "vec3.h"

#include <iostream>

int main() {

    const int width = 256;
    const int height = 256;

    // header: image params
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    // the original had a prefix increment for some reason
    for (int j = height-1; j >= 0; j--) {
        std::cerr << "\r" << j << " lines left" << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            color pixel(
                double(i) / (width-1),
                double(j) / (height-1),
                0.25
            );
            write_color(std::cout, pixel);
        }
    }
}
