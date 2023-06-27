#pragma once

#include <raylib.h>

#include <string>

namespace render {
class Texture {
public:
    explicit Texture(const std::string &filename);
    ~Texture();

    Texture(const Texture &) = delete;
    Texture(Texture &&) noexcept;

    Texture &operator=(const Texture &other) = delete;
    Texture &operator=(Texture &&other) noexcept;

    [[nodiscard]] Texture2D Get() const noexcept;

    [[nodiscard]] int GetWidth() const noexcept;
    [[nodiscard]] int GetHeight() const noexcept;

private:
    Texture2D texture_ {};

    void Unload() const noexcept;
};
}  // namespace render