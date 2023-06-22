#pragma once

#include <entt/entt.hpp>

namespace ecs {

class System {
public:
    virtual void Update(entt::registry &registry) = 0;
};

}  // namespace ecs