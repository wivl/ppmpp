#include <iostream>

#include "ppmpp.hpp"


int main(void) {
    ppm::Image image(800, 600);
    // 0xAABBGGRR
    image.set(400, 300, 0xFFFFFFFF);
    image.save("example.ppm");
    return 0;
}
