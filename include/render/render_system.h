#pragma once

#include "ecs/system.h"

namespace render {

class RenderSystem final : public ecs::System {
public:
    void Update(entt::registry &registry) noexcept override;
};

}  // namespace render