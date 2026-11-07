#include "image_processing/operations.hpp"
#include <cassert>

int main() {
    image_processing::Image image(2, 2);
    image.at(0, 0, 0) = 255; image.at(0, 0, 1) = 0; image.at(0, 0, 2) = 0;
    auto gray = image_processing::grayscale(image);
    assert(gray.width == 2 && gray.height == 2);
    assert(gray.at(0, 0, 0) == gray.at(0, 0, 1) && gray.at(0, 0, 1) == gray.at(0, 0, 2));
    auto small = image_processing::crop(image, 0, 0, 1, 1);
    assert(small.width == 1 && small.height == 1 && small.at(0, 0, 0) == 255);
    auto large = image_processing::resize_nearest(small, 3, 2);
    assert(large.width == 3 && large.height == 2 && large.at(2, 1, 0) == 255);
}
