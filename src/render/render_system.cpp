#include "render/render_system.h"

#include <raylib.h>

#include "ecs/components/sprite.h"
#include "ecs/components/transform.h"

namespace comp = ecs::components;

namespace render {

void RenderSystem::Update(entt::registry &registry) noexcept {
    auto view = registry.view<comp::Transform, comp::Sprite>();

    BeginDrawing();
    ClearBackground(BLACK);

    view.each([](auto &transform, auto &sprite) {
        DrawTexture(sprite.texture->Get(), transform.position.x, transform.position.y, WHITE);
    });

    EndDrawing();
}

}  // namespace render