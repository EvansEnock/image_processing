#pragma once

#include <cstdint>
#include <vector>

namespace image_processing 
{

    // Pixels are stored row by row in RGB order, with three bytes per pixel.
    struct Image 
    {
        int width = 0;
        int height = 0;
        std::vector<std::uint8_t> pixels;

        Image() = default;
        Image(int width, int height);

        std::uint8_t& at(int x, int y, int channel);
        const std::uint8_t& at(int x, int y, int channel) const;
        bool valid() const noexcept;
    };

} // namespace image_processing
