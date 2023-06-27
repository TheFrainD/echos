#pragma once

#include <cstdint>
#include <string>

namespace core {
struct Window {
    std::uint32_t width;
    std::uint32_t height;
    std::string title;
};
}  // namespace core