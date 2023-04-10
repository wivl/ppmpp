# ppmpp

[ppm](http://people.uncw.edu/tompkinsj/112/texnh/assignments/imageFormat.html) encoder and decoder for cpp.

ppm format is actually really easy. But if you are too lazy to write your own encoder/decoder, just copy the <code>ppmpp.hpp</code> and <code>ppmpp.cpp</code> to your project.

The code is under [WTFPL](https://en.wikipedia.org/wiki/WTFPL). It means you can do what the fuck you want to the code.

## example

```cpp
#include <iostream>
#include "ppmpp.hpp"

// This program saves 3 images:
// create.ppm: black background and white square;
//
// from_raw.ppm: using static function <code>ppm::Image::write()</code> to write
//          directly from std::vector<uint32_t> pixels.
// read_example.ppm: read create.ppm and save
int main(void) {
    // define colors
    ppm::Color white(0xFFFFFFFF);
    ppm::Color red(0xFF0000FF);

    // create image
    ppm::Image image(800, 600);
    for (int h = 200-1; h <= 400-1; h++) {
        for (int w = 200-1; w <= 600-1; w++) {
            //                 0xAABBGGRR
            // image.set(w, h, 0xFFFFFFFF);
            // or:
            image.set(w, h, white);
        }
    }
    // Create another image from raw pixels(uint32_t, 0xAABBGGRR)
    ppm::Image::write("from_raw.ppm", image.get_pixels(), image.get_width(), image.get_height());
    image.save("create.ppm");

    // read
    ppm::Image read_example("create.ppm");
    // or read from raw:
    // int width, height
    // ppm::Image::load("create.ppm", width, height);
    // std::cout << "width height: " << width << " " << height << std::endl;
    read_example.save("read_example.ppm");
    return 0;
}
```

result(to show in markdown I transform it to png):

![example.ppm](./assets/example.png)
