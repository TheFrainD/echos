#pragma once

#include <raylib.h>

#include <cstdint>
#include <memory>

namespace ecs::components {

struct Sprite {
    std::shared_ptr<Texture2D> texture;
};

}  // namespace ecs::components