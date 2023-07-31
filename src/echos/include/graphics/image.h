#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

namespace graphics {
class ImageLoadingError : public std::runtime_error {
public:
    explicit ImageLoadingError(const std::string &filename)
        : std::runtime_error("Failed to an load image at " + filename) {}
};

class Image {
public:
    enum Format : std::int32_t { kRgb = 3, kRgba = 4 };

    explicit Image(const std::string &filename);
    ~Image();

    Image(const Image &) = delete;
    Image(Image &&other) noexcept;

    Image &operator=(const Image &) = delete;
    Image &operator=(Image &&other) noexcept;

    [[nodiscard]] std::int32_t GetWidth() const noexcept;
    [[nodiscard]] std::int32_t GetHeight() const noexcept;
    [[nodiscard]] Format GetFormat() const noexcept;
    [[nodiscard]] std::uint8_t *GetData() const noexcept;

private:
    std::int32_t width_;
    std::int32_t height_;
    std::int32_t format_;
    std::uint8_t *data_;

    void Release() noexcept;
};
}  // namespace graphics