#include <raylib.h>

#include <entt/entt.hpp>
#include <memory>

#include "core/game.h"
#include "physics/components/transform.h"
#include "render/components/sprite.h"

using namespace entt::literals;

int main(int argc, char **argv) {
    const auto game {std::make_unique<core::Game>(800, 600, "Echos")};
    auto &registry {game->GetRegistry()};
    auto &cache_manager {game->GetCacheManager()};

    cache_manager.AddResource<render::Texture>("sky_sprite"_hs, "../assets/sprites/sky.png");
    auto texture {cache_manager.GetResource<render::Texture>("sky_sprite"_hs)};

    const auto sky {registry.create()};
    registry.emplace<physics::components::Transform>(sky, Vector2 {400.0, 300.0});
    registry.emplace<render::components::Sprite>(sky, texture);

    game->Run();

    return 0;
}