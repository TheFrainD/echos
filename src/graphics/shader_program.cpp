#include "graphics/shader_program.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace graphics {
ShaderProgram::ShaderProgram() : id_(glCreateProgram()) {}

ShaderProgram::ShaderProgram(const Shader &vertex, const Shader &fragment) : ShaderProgram() {
    Attach(vertex);
    Attach(fragment);
    Link();
}

ShaderProgram::ShaderProgram(const Shader &vertex, const Shader &fragment, const Shader &geometry) : ShaderProgram() {
    Attach(vertex);
    Attach(fragment);
    Attach(geometry);
    Link();
}
ShaderProgram::~ShaderProgram() { Release(); }

ShaderProgram::ShaderProgram(ShaderProgram &&other) noexcept
    : id_(other.id_), uniform_locations_(std::move(other.uniform_locations_)) {
    other.id_ = 0;
}

ShaderProgram &ShaderProgram::operator=(ShaderProgram &&other) noexcept {
    if (this != &other) {
        Release();
        std::swap(id_, other.id_);
        std::swap(uniform_locations_, other.uniform_locations_);
    }
    return *this;
}

void ShaderProgram::Attach(const Shader &shader) const { glAttachShader(id_, shader.GetId()); }

void ShaderProgram::Link() const {
    glLinkProgram(id_);

    GLint link_status;
    glGetProgramiv(id_, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        throw ShaderLinkingError {GetInfoLog()};
    }
}
void ShaderProgram::Use() const { glUseProgram(id_); }

ShaderProgram::UniformLocation ShaderProgram::GetUniformLocation(const std::string &name) {
    if (!uniform_locations_.contains(name)) {
        uniform_locations_[name] = glGetUniformLocation(id_, name.c_str());
    }
    return uniform_locations_.at(name);
}

void ShaderProgram::SetUniformFloat(const std::string &name, const float value) {
    Use();
    glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniformFloatArray(const std::string &name, const std::span<float> &array) {
    Use();
    glUniform1fv(GetUniformLocation(name), array.size(), array.data());
}

void ShaderProgram::SetUniformVector2(const std::string &name, const glm::vec2 &vector) {
    Use();
    glUniform2f(GetUniformLocation(name), vector.x, vector.y);
}

void ShaderProgram::SetUniformVector3(const std::string &name, const glm::vec3 &vector) {
    Use();
    glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
}

void ShaderProgram::SetUniformVector4(const std::string &name, const glm::vec4 &vector) {
    Use();
    glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::SetUniformMatrix4(const std::string &name, const glm::mat4 &matrix) {
    Use();
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::SetUniformInteger(const std::string &name, const std::int32_t value) {
    Use();
    glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniformIntegerArray(const std::string &name, const std::span<std::int32_t> &array) {
    Use();
    glUniform1iv(GetUniformLocation(name), array.size(), array.data());
}

void ShaderProgram::Release() noexcept {
    if (id_ != 0) {
        glDeleteProgram(id_);
        uniform_locations_.clear();
        id_ = 0;
    }
}
std::string ShaderProgram::GetInfoLog() const {
    GLint length;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &length);

    if (length > 0) {
        std::string info_log(length, 0);
        glGetProgramInfoLog(id_, length, &length, info_log.data());
        return info_log;
    }

    return {};
}
}  // namespace graphics