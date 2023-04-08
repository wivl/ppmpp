/*     DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE

Copyright (c) 2023 wivl. All rights reserved.

Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

    DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
    0. You just DO WHAT THE FUCK YOU WANT TO. */

#ifndef __PPMPP_H__
#define __PPMPP_H__

#include <cstdint>
#include <vector>
#include <iostream>

namespace ppm {

    class Image {
        private:
            std::vector<uint32_t> pixels;
            int width;
            int height;
        public:

            static void write(const char *filename, std::vector<uint32_t> pixels, int width, int height);

            Image();
            Image(int width, int height);

            // TODO: I currently don't care about read a ppm image from file.
            // Image(const char *filename);

            int get_width();
            int get_height();


            std::vector<uint32_t> get_pixels();

            void set(int w, int h, uint32_t pixel);
            uint32_t get(int w, int h);

            void save(const char *filename);
            
            Image &operator=(const Image &other) {
                if (this != &other) {
                    this->height = other.height;
                    this->width = other.width;
                    this->pixels = other.pixels;
                }
                return *this;
            }

            uint32_t &operator[](int index) {
                if (index < 0 || index >= width*height) {
                    std::cerr << "ppmpp: Index out of range: " << index << std::endl;
                    exit(1);
                }
                return pixels[index];
            }

    };

}

#endif // !__PPMPP_H__
