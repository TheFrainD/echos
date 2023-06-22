#include "core/game.h"

#include <raylib.h>

namespace core {

Game::Game(std::uint32_t width, std::uint32_t height, const std::string& title) : window_ {width, height, title} {}

Game::~Game() { Shutdown(); }

void Game::Run() noexcept {
    Start();
    Loop();
}

void Game::Start() noexcept {
    is_running_ = true;
    InitWindow(window_.width, window_.height, window_.title.c_str());
}

void Game::Loop() noexcept {
    while (is_running_) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Echos are coming after you...", 300, 300, 20, LIGHTGRAY);

        EndDrawing();

        if (WindowShouldClose()) {
            is_running_ = false;
        }
    }
}

void Game::Shutdown() noexcept { CloseWindow(); }

}  // namespace core