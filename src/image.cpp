#include "image_processing/image.hpp"
#include <limits>
#include <stdexcept>

namespace image_processing 
{
    namespace 
    {
        std::size_t checked_size(int width, int height) 
        {
            if (width <= 0 || height <= 0) 
                throw std::invalid_argument("image dimensions must be positive");

            const auto w = static_cast<std::size_t>(width);
            const auto h = static_cast<std::size_t>(height);

            if (w > std::numeric_limits<std::size_t>::max() / h / 3)
                throw std::length_error("image dimensions are too large");
            
            return w * h * 3;
        }
    }

    Image::Image(int w, int h) : width(w), height(h), pixels(checked_size(w, h)) {}

    std::uint8_t& Image::at(int x, int y, int channel) 
    {
        if (x < 0 || x >= width || y < 0 || y >= height || channel < 0 || channel >= 3)
            throw std::out_of_range("pixel coordinate is outside the image");
        
        return pixels[(static_cast<std::size_t>(y) * width + x) * 3 + channel];
    }

    const std::uint8_t& Image::at(int x, int y, int channel) const 
    {
        if (x < 0 || x >= width || y < 0 || y >= height || channel < 0 || channel >= 3)
            throw std::out_of_range("pixel coordinate is outside the image");
        
        return pixels[(static_cast<std::size_t>(y) * width + x) * 3 + channel];
    }

    bool Image::valid() const noexcept 
    {
        return width > 0 && height > 0 && pixels.size() == static_cast<std::size_t>(width) * height * 3;
    }
} // namespace image_processing
