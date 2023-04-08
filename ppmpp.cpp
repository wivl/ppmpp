/*     DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE

Copyright (c) 2023 wivl. All rights reserved.

Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

    DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
    0. You just DO WHAT THE FUCK YOU WANT TO. */

#include "ppmpp.hpp"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

void ppm::Image::write(const char *filename, std::vector<uint32_t> pixels, int width, int height) {
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) {
        std::cerr << "ppmpp: Error creating file: " << filename << std::endl;
        exit(1);
    }
    outfile << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < width*height; i++) {
        uint32_t pixel = pixels[i];
        uint8_t bytes[3];
        for (int j = 0; j < 3; j++) {
            bytes[j] = (pixel >> (8*j)) & 0xFF;
            outfile << bytes[j];
        }
    }
    outfile.close();

}

ppm::Image::Image() {
    width = 0;
    height = 0;
}

ppm::Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    std::vector<uint32_t> pixels(this->width*this->height);
    this->pixels = pixels;
}



// TODO: I currently don't care about read a ppm image from file.
// Image(const char *filename);

int ppm::Image::get_width() {
    return width;
}
int ppm::Image::get_height() {
    return height;
}

std::vector<uint32_t> ppm::Image::get_pixels() {
    return pixels;
}



void ppm::Image::set(int w, int h, uint32_t pixel) {
    if (w >= width || h >= height) {
        std::cerr << "ppmpp: Invalid w/h value." << std::endl;
        exit(1);
    }
    pixels[h*width+w] = pixel;
}
uint32_t ppm::Image::get(int w, int h) {
    if (w >= width || h >= height) {
        std::cerr << "ppmpp: Invalid w/h value" << std::endl;
        exit(1);
    }
    return pixels[h*width+w];
}

void ppm::Image::save(const char *filename) {
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) {
        std::cerr << "ppmpp: Error creating file: " << filename << std::endl;
        exit(1);
    }
    outfile << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < width*height; i++) {
        // AABBGGRR
        uint32_t pixel = pixels[i];
        uint8_t bytes[3];
        for (int j = 0; j < 3; j++) {
            bytes[j] = (pixel >> (8*j)) & 0xFF;
            outfile << bytes[j];
        }
    }
    outfile.close();
}


