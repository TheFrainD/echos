#include <raylib.h>

#include <entt/entt.hpp>
#include <memory>

#include "core/components/player_controller.h"
#include "core/game.h"
#include "physics/components/transform.h"
#include "render/components/sprite.h"

using namespace entt::literals;

int main(int argc, char **argv) {
    const auto game {std::make_unique<core::Game>(800, 600, "Echos")};
    auto &registry {game->GetRegistry()};
    auto &cache_manager {game->GetCacheManager()};

    cache_manager.AddResource<render::Texture>("sky_sprite"_hs, "assets/sprites/sky.png");
    auto sky_texture {cache_manager.GetResource<render::Texture>("sky_sprite"_hs)};

    const auto sky {registry.create()};
    registry.emplace<physics::components::Transform>(sky, Vector2 {400.0, 300.0});
    registry.emplace<render::components::Sprite>(sky, sky_texture);

    cache_manager.AddResource<render::Texture>("player_texture"_hs, "assets/sprites/player.png");
    auto player_texture {cache_manager.GetResource<render::Texture>("player_texture"_hs)};

    const auto player {registry.create()};
    registry.emplace<physics::components::Transform>(player, Vector2 {200.0, 300.0});
    registry.emplace<render::components::Sprite>(player, player_texture);
    registry.emplace<core::components::PlayerController>(player, 80.0f);

    game->Run();

    return 0;
}