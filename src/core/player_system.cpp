#include "core/player_system.h"

#include <raylib.h>

#include "core/components/player_controller.h"
#include "input/action.h"
#include "physics/components/transform.h"

namespace core {
void PlayerSystem::Update(entt::registry &registry) noexcept {
    const auto view {registry.view<physics::components::Transform, components::PlayerController>()};

    input::Action<bool> up {{KEY_W, KEY_UP}};
    input::Action<bool> down {{KEY_S, KEY_DOWN}};
    input::Action<bool> left {{KEY_A, KEY_LEFT}};
    input::Action<bool> right {{KEY_D, KEY_RIGHT}};

    view.each([&](auto &transform, auto &player_controller) {
        Vector2 direction {};

        up.Update();
        down.Update();
        left.Update();
        right.Update();

        if (up.GetValue()) {
            direction.y = -1;
        } else if (down.GetValue()) {
            direction.y = 1;
        }

        if (left.GetValue()) {
            direction.x = -1;
        } else if (right.GetValue()) {
            direction.x = 1;
        }

        auto translation {Vector2Scale(Vector2Normalize(direction), GetFrameTime() * player_controller.speed)};
        transform.position = Vector2Add(transform.position, translation);
    });
}
}  // namespace core