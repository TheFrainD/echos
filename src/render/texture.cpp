#include "render/texture.h"

namespace render {

Texture::Texture(const std::string &filename) { texture_ = LoadTexture(filename.c_str()); }

Texture::~Texture() { UnloadTexture(texture_); }

Texture2D Texture::Get() const noexcept { return texture_; }

}  // namespace render