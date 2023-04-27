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

    class Color {
        private:
            uint32_t raw;
            std::vector<uint8_t> abgr;
        public:
            Color();
            Color(uint32_t pixel);
            Color(uint8_t r, uint8_t g, uint8_t b);
            Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

            uint32_t get_raw() const;
            uint8_t get_r() const;
            uint8_t get_g() const;
            uint8_t get_b() const;
            uint8_t get_a() const;

            void intensity(float intensity);

            Color &operator=(const Color &other) {
                if (this != &other) {
                    this->raw = other.raw;
                    this->abgr = other.abgr;
                }
                return *this;
            }
            
            Color operator+(const Color& c2) {
                uint8_t r = std::min(255, int(this->get_r()) + 
int(c2.get_r()));
                uint8_t g = std::min(255, int(this->get_g()) + int(c2.get_g()));
                uint8_t b = std::min(255, int(this->get_b()) + int(c2.get_b()));
                uint8_t a = std::min(255, int(this->get_a()) + int(c2.get_a()));
                return Color(r, g, b, a);
            }

            uint8_t &operator[](int index) {
                if (index < 0 || index >= 4) {
                    std::cerr << "ppmpp: Index out of range: " << index << std::endl;
                    exit(1);
                }
                return abgr[index];
            }

    };

    class Image {
        private:
            std::vector<uint32_t> pixels;
            int width;
            int height;
        public:

            static void write(const char *filename, std::vector<uint32_t> pixels, int width, int height);
            static std::vector<uint32_t> load(const char *filename, int &width, int &height);

            Image();
            Image(int width, int height);

            Image(const char *filename);

            int get_width();
            int get_height();


            std::vector<uint32_t> get_pixels();
            void load(const char *filename);

            void set(int w, int h, uint32_t pixel);
            void set(int w, int h, ppm::Color color);
            uint32_t get(int w, int h);

            Color get_color(int w, int h);

            void save(const char *filename);

            ppm::Image vfliped();
            void vflip();
            
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
