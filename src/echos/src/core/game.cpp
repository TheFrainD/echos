#include "core/game.h"

#include <spdlog/spdlog.h>

namespace core {
Game::Game(const std::uint32_t width, const std::uint32_t height, const std::string &title)
    : window_ {width, height, title} {}

Game::~Game() { Shutdown(); }

void Game::Run() noexcept {
    SetupLogger();

    try {
        window_.Open();
    } catch (const WindowException &ex) {
        spdlog::critical(ex.what());
        return;
    }

    Start();
    Loop();
}

entt::registry &Game::GetRegistry() noexcept { return registry_; }

void Game::Start() noexcept { is_running_ = true; }

void Game::Loop() noexcept {
    while (is_running_) {
        Window::PollEvents();

        try {
            window_.SwapBuffers();
        } catch (const WindowException &ex) {
            spdlog::critical(ex.what());
            is_running_ = false;
            break;
        }

        player_system_.Update(registry_);

        render_system_.Update(registry_);

        if (window_.ShouldClose()) {
            is_running_ = false;
        }
    }
}

void Game::Shutdown() noexcept {}

resource::CacheManager &Game::GetCacheManager() noexcept { return cache_manager_; }

void Game::SetupLogger() noexcept {
    spdlog::set_pattern("%^[%X] %l: %v%$");
#ifdef NDEBUG
    spdlog::set_level(spdlog::level::info);
#else
    spdlog::set_level(spdlog::level::debug);
#endif
}
}  // namespace core