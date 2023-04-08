#include <iostream>

#include "ppmpp.hpp"


// This program saves 2 images:
// example.ppm: black background and white square;
//
// write.ppm: using static function <code>ppm::Image::write()</code> to write
//          directly from std::vector<uint32_t> pixels.
int main(void) {
    ppm::Color color(0xFFFFFFFF);
    ppm::Image image(800, 600);
    for (int h = 200-1; h <= 400-1; h++) {
        for (int w = 200-1; w <= 600-1; w++) {
            //              0xAABBGGRR
            image.set(w, h, 0xFFFFFFFF);
            // or:
            // image.set(w, h, color);
        }
    }
    // Create another image from raw pixels(uint32_t, 0xAABBGGRR)
    ppm::Image::write("write.ppm", image.get_pixels(), image.get_width(), image.get_height());

    image.save("example.ppm");
    return 0;
}
