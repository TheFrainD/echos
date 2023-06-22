#pragma once

#include <cstdint>
#include <entt/entt.hpp>
#include <string>

#include "core/window.h"
#include "render/render_system.h"

namespace core {

class Game {
public:
    Game(std::uint32_t width, std::uint32_t height, const std::string &title);
    ~Game();

    void Run() noexcept;

    entt::registry &GetRegistry() noexcept;

private:
    bool is_running_ {false};
    Window window_;
    entt::registry registry_;
    render::RenderSystem render_system_;

    void Start() noexcept;
    void Loop() noexcept;
    void Shutdown() noexcept;
};

}  // namespace core