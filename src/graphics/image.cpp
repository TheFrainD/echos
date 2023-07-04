#include "graphics/image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace graphics {
Image::Image(const std::string &filename)
    : data_(stbi_load(filename.c_str(), &width_, &height_, &format_, STBI_rgb_alpha)) {
    if (!data_) {
        throw ImageLoadingError {filename};
    }
}

Image::~Image() { Release(); }

Image::Image(Image &&other) noexcept
    : width_(other.width_), height_(other.height_), format_(other.format_), data_(other.data_) {
    other.data_ = nullptr;
}

Image &Image::operator=(Image &&other) noexcept {
    if (this != &other) {
        Release();
        std::swap(width_, other.width_);
        std::swap(height_, other.height_);
        std::swap(format_, other.format_);
        std::swap(data_, other.data_);
    }
    return *this;
}

void Image::Release() noexcept {
    if (data_ != nullptr) {
        stbi_image_free(data_);
        data_ = nullptr;
    }
}

std::int32_t Image::GetWidth() const noexcept { return width_; }

std::int32_t Image::GetHeight() const noexcept { return height_; }

Image::Format Image::GetFormat() const noexcept { return static_cast<Format>(format_); }

std::uint8_t *Image::GetData() const noexcept { return data_; }
}  // namespace graphics