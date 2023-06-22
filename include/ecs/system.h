#pragma once

#include <cassert>
#include <entt/entt.hpp>

namespace ecs {

class System {
public:
    virtual void Update(entt::registry &registry) noexcept = 0;
};

}  // namespace ecs