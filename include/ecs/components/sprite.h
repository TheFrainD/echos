#pragma once

#include <entt/resource/resource.hpp>

#include "render/texture.h"

namespace ecs::components {

struct Sprite {
    entt::resource<render::Texture> texture;
};

}  // namespace ecs::components