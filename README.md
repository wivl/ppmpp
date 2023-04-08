# ppmpp

[ppm](http://people.uncw.edu/tompkinsj/112/texnh/assignments/imageFormat.html) encoder for cpp.

> Doesn't support ppm decode (read).

Who needs this?

Maybe you have an array of pixels, and wants to save an image and don't care about shit, you can try this.

ppm format is actually really easy. But if you are too lazy to write your own encoder, just copy the <code>ppmpp.hpp</code> and <code>ppmpp.cpp</code> to your project.

The code is under [WTFPL](https://en.wikipedia.org/wiki/WTFPL). It means you can do what the fuck you want with the code.

## example

```cpp
#include <iostream>
#include "ppmpp.hpp"

// This program saves 2 images:
// example.ppm: black background and white square;
//
// write.ppm: using static function <code>ppm::Image::write()</code> to write
//          directly from std::vector<uint32_t> pixels.
int main(void) {
    ppm::Image image(800, 600);
    for (int h = 200-1; h <= 400-1; h++) {
        for (int w = 200-1; w <= 600-1; w++) {
            //              0xAABBGGRR
            image.set(w, h, 0xFFFFFFFF);
        }
    }
    // Create another image from raw pixels(uint32_t, 0xAABBGGRR)
    ppm::Image::write("write.ppm", image.get_pixels(), image.get_width(), image.get_height());

    image.save("example.ppm");
    return 0;
}
```

result(to show in markdown I transform it to png):

![example.ppm](./assets/example.png)
