#include "core/window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace {
void GlfwErrorCallback(int error_code, const char *message) { spdlog::error("GLFW Error #{}: {}", error_code, message); }
}  // namespace

namespace core {
bool Window::glfw_initialized_ {false};

Window::Window(const std::uint32_t width, const std::uint32_t height, const std::string &title)
    : data_ {width, height, title} {
    glfwSetErrorCallback(GlfwErrorCallback);

    if (!glfw_initialized_) {
        if (!glfwInit()) {
            throw std::runtime_error {"Failed to initialize GLFW"};
        }
        spdlog::info("GLFW initialized");
        glfw_initialized_ = true;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    handle_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (handle_ == nullptr) {
        glfwTerminate();
        throw std::runtime_error {"Failed to create window"};
    }

    spdlog::info("Created window");

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
        throw std::runtime_error {"Failed to initialize glad"};
    }

    glViewport(0, 0, width, height);

    spdlog::debug("Vendor: {}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    spdlog::debug("Renderer: {}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    spdlog::debug("OpenGL version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    spdlog::debug("GLSL version: {}", reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
}

Window::~Window() {
    if (handle_) {
        glfwDestroyWindow(handle_);
    }
    if (glfw_initialized_) {
        glfwTerminate();
    }
}

void Window::PollEvents() noexcept { glfwPollEvents(); }

void Window::SwapBuffers() const noexcept { glfwSwapBuffers(handle_); }

bool Window::ShouldClose() const noexcept { return glfwWindowShouldClose(handle_) != 0; }
}  // namespace core
