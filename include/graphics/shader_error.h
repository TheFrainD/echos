#pragma once

#include "graphics/error.h"

namespace graphics {
class ShaderError : public Error {
public:
    explicit ShaderError(const std::string &arg) : Error {arg} {}
};
}  // namespace graphics