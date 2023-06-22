#pragma once

#include <cstdint>
#include <string>

#include "core/window.h"

namespace core {

class Game {
public:
    Game(std::uint32_t width, std::uint32_t height, const std::string &title);
    ~Game();

    void Run() noexcept;

private:
    bool is_running_ {false};
    Window window_;

    void Start() noexcept;
    void Loop() noexcept;
    void Shutdown() noexcept;
};

}  // namespace core