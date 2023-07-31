#include "core/player_system.h"

#include "core/components/player_controller.h"
#include "physics/components/transform.h"

namespace core {
void PlayerSystem::Update(entt::registry &registry) noexcept {
    const auto view {registry.view<physics::components::Transform, components::PlayerController>()};

    view.each([](auto &transform, auto &player_controller) {
//        Vector2 direction {};
//
//        if (IsKeyDown(KEY_W)) {
//            direction.y = -1;
//        } else if (IsKeyDown(KEY_S)) {
//            direction.y = 1;
//        }
//
//        if (IsKeyDown(KEY_A)) {
//            direction.x = -1;
//        } else if (IsKeyDown(KEY_D)) {
//            direction.x = 1;
//        }
//
//        auto translation {Vector2Scale(Vector2Normalize(direction), GetFrameTime() * player_controller.speed)};
//        transform.position = Vector2Add(transform.position, translation);
    });
}
}  // namespace core