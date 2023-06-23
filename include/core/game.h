#pragma once

#include <cstdint>
#include <entt/entt.hpp>
#include <string>

#include "core/resource/cache.h"
#include "core/window.h"
#include "render/render_system.h"
#include "render/texture.h"

namespace core {

class Game {
public:
    Game(std::uint32_t width, std::uint32_t height, const std::string &title);
    ~Game();

    void Run() noexcept;

    entt::registry &GetRegistry() noexcept;
    resource::Cache<render::Texture> &GetTextureCache() noexcept;

private:
    bool is_running_ {false};
    Window window_;
    entt::registry registry_;
    resource::Cache<render::Texture> texture_cache_ {};
    render::RenderSystem render_system_;

    void Start() noexcept;
    void Loop() noexcept;
    void Shutdown() noexcept;
};

}  // namespace core