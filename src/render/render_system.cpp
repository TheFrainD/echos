#include "render/render_system.h"

#include "physics/components/transform.h"
#include "render/components/sprite.h"

namespace render {
void RenderSystem::Update(entt::registry &registry) noexcept {
    const auto view = registry.view<physics::components::Transform, components::Sprite>();

//    BeginDrawing();
//    ClearBackground(BLACK);
//
//    view.each([](auto &transform, auto &sprite) {
//        DrawTexture(sprite.texture->Get(), transform.position.x, transform.position.y, WHITE);
//    });
//
//    EndDrawing();
}
}  // namespace render