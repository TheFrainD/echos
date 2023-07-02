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

    void Open();
    void Close() noexcept;
    static void PollEvents() noexcept;
    void SwapBuffers() const;

    [[nodiscard]] bool ShouldClose() const noexcept;

private:
    static bool glfw_initialized_;
    static std::size_t windows_opened_;
    GLFWwindow *handle_ {nullptr};
    WindowData data_;
};

class WindowException : public std::exception {
public:
    explicit WindowException(std::string message);
    [[nodiscard]] const char *what() const noexcept override;

private:
    std::string message_;
};
}  // namespace core