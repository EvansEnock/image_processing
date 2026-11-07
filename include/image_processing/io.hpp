#pragma once

#include "image_processing/image.hpp"
#include <filesystem>

namespace image_processing
{
	Image load_image(const std::filesystem::path& path);

	void save_image(const Image& image, const std::filesystem::path& path);
} // namespace image_processing
