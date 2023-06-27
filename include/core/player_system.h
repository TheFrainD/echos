#pragma once

#include "ecs/system.h"

namespace core {
class PlayerSystem final : public ecs::System {
public:
    void Update(entt::registry &registry) noexcept override;
};
}  // namespace core