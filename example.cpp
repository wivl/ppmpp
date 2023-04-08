#include <iostream>

#include "ppmpp.hpp"


int main(void) {
    ppm::Image image(800, 600);
    // 0xAABBGGRR
    image.set(400, 300, 0xFFFFFFFF);
    ppm::Image::write("write.ppm", image.get_pixels(), image.get_width(), image.get_height());
    image.save("example.ppm");
    return 0;
}
