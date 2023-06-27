#pragma once

#include <entt/entt.hpp>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "core/resource/cache.h"

namespace core::resource {
class CacheManager {
public:
    template <typename T>
    std::shared_ptr<Cache<T>> GetCache() noexcept {
        if (!caches_.contains(typeid(T))) {
            caches_[typeid(T)] = std::make_shared<Cache<T>>();
        }
        return std::static_pointer_cast<Cache<T>>(caches_.at(typeid(T)));
    }

    template <typename T>
    entt::resource<T> GetResource(const entt::id_type id) {
        auto cache {GetCache<T>()};
        return cache->operator[](id);
    }

    template <typename T, typename... Args>
    auto AddResource(const entt::id_type id, Args &&...args) {
        auto cache {GetCache<T>()};
        return cache->load(id, std::forward<Args>(args)...);
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> caches_;
};
}  // namespace core::resource