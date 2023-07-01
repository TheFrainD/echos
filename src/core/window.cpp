#include "core/window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace {
void GlfwErrorCallback(int error_code, const char *message) {
    std::cerr << "GLFW Error #" << error_code << ": " << message << '\n';
}
}  // namespace

namespace core {
bool Window::glfw_initialized_ {false};

Window::Window(const std::uint32_t width, const std::uint32_t height, const std::string &title)
    : data_ {width, height, title} {
    glfwSetErrorCallback(GlfwErrorCallback);

    glewExperimental = GL_TRUE;

    if (!glfw_initialized_) {
        if (!glfwInit()) {
            throw std::runtime_error {"Failed to initialize GLFW"};
        }
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

    glfwSetWindowUserPointer(handle_, &data_);

    glfwSetFramebufferSizeCallback(handle_, [](GLFWwindow *window, int width, int height) {
        auto *const data = static_cast<WindowData *>(glfwGetWindowUserPointer(window));
        data->width      = width;
        data->height     = height;
        glViewport(0, 0, width, height);
    });

    glfwMakeContextCurrent(handle_);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error {"Failed to initialize GLEW"};
    }

    glViewport(0, 0, width, height);
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

bool Window::ShouldClose() const noexcept { return glfwWindowShouldClose(handle_); }
}  // namespace core