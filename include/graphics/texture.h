#pragma once

#include <cstdint>
#include <vector>

#include "graphics/image.h"

namespace graphics {
class Texture {
public:
    enum class Wrapping : std::uint32_t {
        kClampToEdge = 0x812F,
        kRepeat      = 0x2901,
    };

    enum class Filter : std::uint32_t {
        kNearest              = 0x2600,
        kLinear               = 0x2601,
        kNearestMipmapNearest = 0x2700,
        kLinearMipmapNearest  = 0x2701,
        kNearestMipmapLinear  = 0x2702,
        kLinearMipmapLinear   = 0x2703,
    };

    explicit Texture(const Image &image);
    Texture();
    ~Texture();

    Texture(Texture &&other) noexcept;
    Texture &operator=(Texture &&other) noexcept;

    Texture(const Texture &)            = delete;
    Texture &operator=(const Texture &) = delete;

    void Bind(std::uint32_t slot = 0) const noexcept;
    void SetData(const std::vector<std::uint32_t> &data, std::uint32_t width, std::uint32_t height) noexcept;

    void GenerateMipmaps() noexcept;
    void SetWrapping(Wrapping s, Wrapping t) noexcept;
    void SetFilters(Filter min, Filter mag) noexcept;

private:
    std::uint32_t id_;

    void Release() noexcept;
};
}  // namespace graphics