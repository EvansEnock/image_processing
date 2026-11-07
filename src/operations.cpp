#include "image_processing/operations.hpp"
#include <algorithm>
#include <stdexcept>

namespace image_processing 
{
    Image grayscale(const Image& input) 
    {
        if (!input.valid()) 
            throw std::invalid_argument("invalid input image");

        Image out(input.width, input.height);
        
        for (int y = 0; y < input.height; ++y) 
            for (int x = 0; x < input.width; ++x) 
            {
                const auto gray = static_cast<std::uint8_t>(0.299 * input.at(x, y, 0) + 0.587 * input.at(x, y, 1) + 0.114 * input.at(x, y, 2));
                for (int c = 0; c < 3; ++c) 
                    out.at(x, y, c) = gray;
            }
        return out;
    }

    Image crop(const Image& input, int x, int y, int width, int height) 
    {
        if (!input.valid() || x < 0 || y < 0 || width <= 0 || height <= 0 || x > input.width - width || y > input.height - height)
            throw std::invalid_argument("crop rectangle is outside the image");
        
        Image out(width, height);
        
        for (int dy = 0; dy < height; ++dy) 
            for (int dx = 0; dx < width; ++dx)
                for (int c = 0; c < 3; ++c) 
                    out.at(dx, dy, c) = input.at(x + dx, y + dy, c);
        return out;
    }

    Image resize_nearest(const Image& input, int width, int height) 
    {
        if (!input.valid() || width <= 0 || height <= 0) 
            throw std::invalid_argument("image and output dimensions must be valid");
        
        Image out(width, height);
        
        for (int y = 0; y < height; ++y) 
            for (int x = 0; x < width; ++x) 
            {
                const int sx = std::min(input.width - 1, static_cast<int>((static_cast<long long>(x) * input.width) / width));
                const int sy = std::min(input.height - 1, static_cast<int>((static_cast<long long>(y) * input.height) / height));
                
                for (int c = 0; c < 3; ++c) 
                    out.at(x, y, c) = input.at(sx, sy, c);
            }
        
        return out;
    }
} // namespace image_processing
