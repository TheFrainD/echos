#include "graphics/texture.h"

#include <glad/glad.h>

#define PUSH_STATE()  \
    GLint restore_id; \
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &restore_id);

#define POP_STATE() glBindTexture(GL_TEXTURE_2D, restore_id);

namespace graphics {
Texture::Texture(const Image &image) {
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    auto format {image.GetFormat() == Image::Format::kRgba ? GL_RGBA : GL_RGB};
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 image.GetData());

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture() { glGenTextures(1, &id_); }

Texture::~Texture() { Release(); }

Texture::Texture(Texture &&other) noexcept : id_(other.id_) { other.id_ = 0; }

Texture &Texture::operator=(Texture &&other) noexcept {
    if (this != &other) {
        Release();
        std::swap(id_, other.id_);
    }
    return *this;
}

void Texture::Bind(const std::uint32_t slot) const noexcept {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::SetData(const std::vector<std::uint32_t> &data, const std::uint32_t width,
                      const std::uint32_t height) noexcept {
    PUSH_STATE();

    glBindTexture(GL_TEXTURE_2D, id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    POP_STATE();
}

void Texture::GenerateMipmaps() noexcept {
    PUSH_STATE();

    glBindTexture(GL_TEXTURE_2D, id_);
    glGenerateMipmap(GL_TEXTURE_2D);

    POP_STATE();
}

void Texture::SetWrapping(Texture::Wrapping s, Texture::Wrapping t) noexcept {
    PUSH_STATE();

    glBindTexture(GL_TEXTURE_2D, id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(s));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(t));

    POP_STATE();
}

void Texture::SetFilters(Texture::Filter min, Texture::Filter mag) noexcept {
    PUSH_STATE();

    glBindTexture(GL_TEXTURE_2D, id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(min));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(mag));

    POP_STATE();
}

void Texture::Release() noexcept {
    if (id_ != 0) {
        glDeleteTextures(1, &id_);
        id_ = 0;
    }
}
}  // namespace graphics