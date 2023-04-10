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

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

ppm::Color::Color() {
    raw = 0;
}

ppm::Color::Color(uint32_t pixel) {
    raw = pixel;
    for (int i = 3; i >= 0; i--) {
        uint8_t tmp = (pixel >> (8*i)) & 0xFF;
        abgr.push_back(tmp);
    }
}
ppm::Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    abgr.push_back(0xFF);
    abgr.push_back(b);
    abgr.push_back(g);
    abgr.push_back(r);
    raw = 0xFF000000 + 
        ((b << (2*8)) & 0xFF0000) + 
        ((g << (1*8)) & 0xFF00) + 
        ((r << (0*8)) & 0xFF);

}

ppm::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    abgr.push_back(a);
    abgr.push_back(b);
    abgr.push_back(g);
    abgr.push_back(r);
    raw = ((a << (3*8)) & 0xFF000000) +
        ((b << (2*8)) & 0xFF0000) + 
        ((g << (1*8)) & 0xFF00) + 
        ((r << (0*8)) & 0xFF);
}

uint32_t ppm::Color::get_raw() {
    return raw;
}

uint8_t ppm::Color::get_r() {
    return abgr[3];
}

uint8_t ppm::Color::get_g() {
    return abgr[2];
}

uint8_t ppm::Color::get_b() {
    return abgr[1];
}

uint8_t ppm::Color::get_a() {
    return abgr[0];
}

void ppm::Color::intensity(float intensity) {
    intensity = intensity < 0 ? 0 : intensity;
    for (int i = 1; i < 4; i++) {
        int tmp = (abgr[i] * intensity) < 255 ?
            (abgr[i] * intensity) : 255;
        abgr[i] = uint8_t(tmp);
    }
    raw = ((abgr[0] << (3*8)) & 0xFF000000) +
        ((abgr[1] << (2*8)) & 0xFF0000) + 
        ((abgr[2] << (1*8)) & 0xFF00) + 
        ((abgr[3] << (0*8)) & 0xFF);
}


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

void ppm::Image::set(int w, int h, ppm::Color color) {
    if (w >= width || h >= height) {
        std::cerr << "ppmpp: Invalid w/h value " << w << "/" << h << " in set()" << std::endl;
        exit(1);
    }
    pixels[h*width+w] = color.get_raw();

}


void ppm::Image::set(int w, int h, uint32_t pixel) {
    if (w >= width || h >= height) {
        std::cerr << "ppmpp: Invalid w/h value " << w << "/" << h << " in set()" << std::endl;
        exit(1);
    }
    pixels[h*width+w] = pixel;
}

uint32_t ppm::Image::get(int w, int h) {
    if (w >= width || h >= height) {
        std::cerr << "ppmpp: Invalid w/h value " << w << "/" << h << " in get()" << std::endl;
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


