#pragma once

#include <cstdint>
#include <string>

struct GLFWwindow;

namespace core {
struct WindowData {
    std::uint32_t width;
    std::uint32_t height;
    std::string title;
};
struct Window {
public:
    Window(std::uint32_t width, std::uint32_t height, const std::string &title);
    ~Window();

    Window(const Window &)            = delete;
    Window &operator=(const Window &) = delete;
    Window(Window &&)                 = delete;
    Window &operator=(Window &&)      = delete;

    static void PollEvents() noexcept;
    void SwapBuffers() const noexcept;

    [[nodiscard]] bool ShouldClose() const noexcept;

private:
    static bool glfw_initialized_;
    GLFWwindow *handle_;
    WindowData data_;
};
}  // namespace core