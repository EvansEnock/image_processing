#pragma once

#include "image_processing/image.hpp"

namespace image_processing 
{
	Image grayscale(const Image& input);
	Image crop(const Image& input, int x, int y, int width, int height);
	Image resize_nearest(const Image& input, int width, int height);
} // namespace image_processing
