#pragma once

#include <raylib.h>

#include <string>
#include <vector>

namespace input {
template <typename T>
class Action {
public:
    explicit Action(std::vector<T> codes) : codes_(std::move(codes)) {}

    void Update() noexcept {}

    [[nodiscard]] T GetValue() const noexcept { return value_; }

private:
    T value_ {};
    std::vector<int> codes_;
};

template <>
class Action<bool> {
public:
    explicit Action(std::vector<int> codes) : codes_(std::move(codes)) {}

    void Update() noexcept {
        for (const auto &code : codes_) {
            if (IsKeyDown(code)) {
                value_ = true;
                break;
            }
        }
    }

    [[nodiscard]] bool GetValue() const noexcept { return value_; }

private:
    bool value_ {};
    std::vector<int> codes_;
};
}