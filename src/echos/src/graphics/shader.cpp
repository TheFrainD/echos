#include "graphics/shader.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace graphics {
Shader::Shader(const Shader::Type type) : id_(glCreateShader(static_cast<GLenum>(type))) {}

Shader::Shader(const Shader::Type type, const std::string &source) : Shader(type) {
    SetSource(source);
    Compile();
}

Shader::~Shader() { Release(); }

Shader::Shader(Shader &&other) noexcept : id_(other.id_) { other.id_ = 0; }

Shader &Shader::operator=(Shader &&other) noexcept {
    if (this != &other) {
        Release();
        std::swap(id_, other.id_);
    }
    return *this;
}

void Shader::SetSource(const std::string &source) const {
    const auto *char_source = source.c_str();
    glShaderSource(id_, 1, &char_source, nullptr);
}

void Shader::Compile() const {
    glCompileShader(id_);

    GLint compile_status;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &compile_status);

    if (compile_status == GL_FALSE) {
        throw ShaderCompilationError {GetInfoLog()};
    }
}

std::uint32_t Shader::GetId() const noexcept { return id_; }

void Shader::Release() noexcept {
    if (id_ != 0) {
        glDeleteShader(id_);
        id_ = 0;
    }
}

std::string Shader::GetInfoLog() const {
    GLint length;
    glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &length);

    if (length > 0) {
        std::string info_log(length, 0);
        glGetShaderInfoLog(id_, length, &length, info_log.data());
        return info_log;
    }

    return {};
};
}  // namespace graphics