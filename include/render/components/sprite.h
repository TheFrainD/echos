#pragma once

#include <entt/resource/resource.hpp>

#include "render/texture.h"

namespace render::components {

struct Sprite {
    entt::resource<Texture> texture;
};

}  // namespace render::components