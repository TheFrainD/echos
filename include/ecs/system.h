#pragma once

#include <entt/entt.hpp>

namespace ecs {
class System {
public:
    System()          = default;
    virtual ~System() = default;

    System(const System &other) = default;
    System(System &&other)      = default;

    System &operator=(const System &other) = default;
    System &operator=(System &&other)      = default;

    virtual void Update(entt::registry &registry) noexcept = 0;
};
}  // namespace ecs