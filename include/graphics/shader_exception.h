#pragma once

#include <stdexcept>

namespace graphics {
class ShaderException : public std::runtime_error {
public:
    explicit ShaderException(const std::string &arg) : std::runtime_error {arg} {}
};
}  // namespace graphics