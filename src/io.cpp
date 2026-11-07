#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "image_processing/io.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>

namespace image_processing 
{
    Image load_image(const std::filesystem::path& path) 
    {
        int width = 0, height = 0, channels = 0;
        const auto name = path.string();
        auto* raw = stbi_load(name.c_str(), &width, &height, &channels, 3);

        if (!raw) 
            throw std::runtime_error("cannot load image '" + name + "': " + stbi_failure_reason());

        Image result(width, height);

        std::copy(raw, raw + result.pixels.size(), result.pixels.begin());

        stbi_image_free(raw);
        return result;
    }

    void save_image(const Image& image, const std::filesystem::path& path) 
    {
        if (!image.valid()) 
            throw std::invalid_argument("cannot save invalid image");

        std::string ext = path.extension().string();

        std::transform
        (
            ext.begin(), ext.end(), ext.begin(), [](unsigned char c) 
            {
                return static_cast<char>(std::tolower(c)); 
            }
        );

        int ok = 0;
        const auto name = path.string();

        if (ext == ".png") 
            ok = stbi_write_png(name.c_str(), image.width, image.height, 3, image.pixels.data(), image.width * 3);
        else if (ext == ".bmp") 
            ok = stbi_write_bmp(name.c_str(), image.width, image.height, 3, image.pixels.data());
        else if (ext == ".jpg" || ext == ".jpeg") 
            ok = stbi_write_jpg(name.c_str(), image.width, image.height, 3, image.pixels.data(), 90);
        else 
            throw std::invalid_argument("output extension must be .png, .bmp, .jpg, or .jpeg");
        
        if (!ok) 
            throw std::runtime_error("failed to write image: " + name);
    }
} // namespace image_processing
