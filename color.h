#ifndef COLOR_H
#define COLOR_H

#include "tracer.h"

#include <iostream>

void write_color(std::ostream &out, color pixel) {
    out << static_cast<int>(255.999 * pixel.r()) << ' '
        << static_cast<int>(255.999 * pixel.g()) << ' '
        << static_cast<int>(255.999 * pixel.b()) << ' '
        << '\n';
}

inline float map_color(float multisample, int samples) {
    return saturate(multisample / float(samples)) * 256; 
}

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    float r = pixel_color.x();
    float g = pixel_color.y();
    float b = pixel_color.z();

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(map_color(r, samples_per_pixel)) << ' '
        << static_cast<int>(map_color(g, samples_per_pixel)) << ' '
        << static_cast<int>(map_color(b, samples_per_pixel)) << '\n';
}

#endif
