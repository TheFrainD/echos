#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "core/player_system.h"
#include "core/resource/cache_manager.h"
#include "core/window.h"
#include "render/render_system.h"

namespace core {
class Game {
public:
    Game(std::uint32_t width, std::uint32_t height, const std::string &title);
    ~Game();

    Game(const Game &) = delete;
    Game(Game &&)      = delete;

    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&)      = delete;

    void Run() noexcept;

    entt::registry &GetRegistry() noexcept;
    resource::CacheManager &GetCacheManager() noexcept;

private:
    bool is_running_ {false};
    std::unique_ptr<Window> window_;
    entt::registry registry_;
    resource::CacheManager cache_manager_;
    render::RenderSystem render_system_;
    PlayerSystem player_system_;

    void Start() noexcept;
    static void SetupLogger() noexcept;
    void Loop() noexcept;
    static void Shutdown() noexcept;
};
}  // namespace core