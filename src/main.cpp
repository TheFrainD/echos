#include <raylib.h>

#include <memory>

#include "core/game.h"
#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"

int main(int argc, char **argv) {
    auto game       = std::make_unique<core::Game>(800, 600, "Echos");
    auto &registery = game->GetRegistry();

    auto texture = std::make_shared<Texture2D>(LoadTexture("../images/parallax-mountain-bg.png"));

    auto sky = registery.create();
    registery.emplace<ecs::components::Transform>(sky, (Vector2) {400.0, 300.0});
    registery.emplace<ecs::components::Sprite>(sky, texture);

    game->Run();

    UnloadTexture(*texture);
    return 0;
}