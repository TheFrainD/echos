#include "render/texture.h"

namespace render {
Texture::Texture(const std::string &filename) { texture_ = LoadTexture(filename.c_str()); }

Texture::~Texture() { Unload(); }

Texture::Texture(Texture &&other) noexcept : texture_(other.texture_) { other.texture_ = {}; }

Texture &Texture::operator=(Texture &&other) noexcept {
    if (this != &other) {
        Unload();

        texture_       = other.texture_;
        other.texture_ = {};
    }

    return *this;
}

Texture2D Texture::Get() const noexcept { return texture_; }

int Texture::GetWidth() const noexcept { return texture_.width; }

int Texture::GetHeight() const noexcept { return texture_.height; }

void Texture::Unload() const noexcept { UnloadTexture(texture_); }
}  // namespace render