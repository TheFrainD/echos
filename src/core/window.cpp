#include "core/window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace {
void GlfwErrorCallback(int error_code, const char *message) {
    spdlog::error("GLFW Error #{}: {}", error_code, message);
}
}  // namespace

namespace core {
bool Window::glfw_initialized_ {false};
std::size_t Window::windows_opened_ {0};

Window::Window(const std::uint32_t width, const std::uint32_t height, const std::string &title)
    : data_ {width, height, title} {}

Window::~Window() { Close(); }

void Window::PollEvents() noexcept { glfwPollEvents(); }

void Window::SwapBuffers() const {
    if (handle_ == nullptr) {
        throw WindowException {"Cannot swap buffers, the window is not open"};
    }
    glfwSwapBuffers(handle_);
}

bool Window::ShouldClose() const noexcept {
    if (handle_ == nullptr) {
        return true;
    }
    return glfwWindowShouldClose(handle_) != 0;
}

void Window::Open() {
    if (handle_ != nullptr) {
        throw WindowException {"Windows is already open"};
    }

    if (!glfw_initialized_) {
        glfwSetErrorCallback(GlfwErrorCallback);
        if (!glfwInit()) {
            throw WindowException {"Failed to initialize GLFW"};
        }
        spdlog::info("GLFW initialized");
        glfw_initialized_ = true;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    handle_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(), nullptr, nullptr);
    if (handle_ == nullptr) {
        glfwTerminate();
        throw WindowException {"Failed to create window"};
    }

    spdlog::info("Window opened");

    glfwSetWindowUserPointer(handle_, &data_);

    glfwSetFramebufferSizeCallback(handle_, [](GLFWwindow *window, int width, int height) {
        auto *const data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));
        data->width      = width;
        data->height     = height;
        glViewport(0, 0, width, height);
    });

    glfwMakeContextCurrent(handle_);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(handle_);
        glfwTerminate();
        throw WindowException {"Failed to load glad"};
    }

    glViewport(0, 0, data_.width, data_.height);

    spdlog::debug("Vendor: {}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    spdlog::debug("Renderer: {}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    spdlog::debug("OpenGL version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    spdlog::debug("GLSL version: {}", reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

    ++windows_opened_;
}

void Window::Close() noexcept {
    if (handle_) {
        glfwDestroyWindow(handle_);
        spdlog::info("Windows closed");
        --windows_opened_;
        
        if (glfw_initialized_ && windows_opened_ == 0) {
            glfwTerminate();
            spdlog::info("GLFW terminated");
        }
    }
}

const char *WindowException::what() const noexcept { return message_.c_str(); }

WindowException::WindowException(std::string message) : message_(std::move(message)) {}
}  // namespace core
