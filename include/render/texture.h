#pragma once

#include <raylib.h>

#include <string>

namespace render {

class Texture {
public:
    explicit Texture(const std::string &filename);
    ~Texture();

    [[nodiscard]] Texture2D Get() const noexcept;

private:
    Texture2D texture_;
};

}  // namespace render