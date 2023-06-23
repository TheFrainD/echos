#pragma once

#include <entt/resource/cache.hpp>

#include "core/resource/loader.h"

namespace core::resource {

template <typename T>
using Cache = entt::resource_cache<T, Loader<T>>;

}