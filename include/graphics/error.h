#pragma once

#include <stdexcept>

namespace graphics {
class Error : public std::runtime_error {
public:
    explicit Error(const std::string &name) : std::runtime_error(name) {}
};
}  // namespace graphics