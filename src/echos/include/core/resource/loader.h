#pragma once

#include <memory>

namespace core::resource {

template <typename T>
class Loader {
public:
    using result_type = std::shared_ptr<T>;

    template <typename... Args>
    result_type operator()(Args &&...args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
};

}  // namespace core::resource