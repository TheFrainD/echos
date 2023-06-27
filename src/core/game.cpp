#include "core/game.h"

#include <raylib.h>

namespace core {
Game::Game(const std::uint32_t width, const std::uint32_t height, const std::string &title)
    : window_ {width, height, title} {
    InitWindow(static_cast<int>(window_.width), static_cast<int>(window_.height), window_.title.c_str());
    SetTargetFPS(60);
}

Game::~Game() { Shutdown(); }

void Game::Run() noexcept {
    Start();
    Loop();
}

entt::registry &Game::GetRegistry() noexcept { return registry_; }

void Game::Start() noexcept { is_running_ = true; }

void Game::Loop() noexcept {
    while (is_running_) {
        render_system_.Update(registry_);

        if (WindowShouldClose()) {
            is_running_ = false;
        }
    }
}

void Game::Shutdown() noexcept { CloseWindow(); }

resource::CacheManager &Game::GetCacheManager() noexcept { return cache_manager_; }
}  // namespace core