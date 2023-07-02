#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <span>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "graphics/shader.h"

namespace graphics {

class ShaderLinkingError : public ShaderError {
public:
    explicit ShaderLinkingError(const std::string &arg) : ShaderError(arg) {}
};

class ShaderProgram {
public:
    using UniformLocation = std::uint32_t;

    ShaderProgram();
    ShaderProgram(const Shader &vertex, const Shader &fragment);
    ShaderProgram(const Shader &vertex, const Shader &fragment, const Shader &geometry);
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram &)            = delete;
    ShaderProgram &operator=(const ShaderProgram &) = delete;

    ShaderProgram(ShaderProgram &&other) noexcept;
    ShaderProgram &operator=(ShaderProgram &&other) noexcept;

    void Attach(const Shader &shader) const;
    void Link() const;
    void Use() const;

    [[nodiscard]] UniformLocation GetUniformLocation(const std::string &name);

    void SetUniformFloat(const std::string &name, float value);
    void SetUniformFloatArray(const std::string &name, const std::span<float> &array);
    void SetUniformVector2(const std::string &name, const glm::vec2 &vector);
    void SetUniformVector3(const std::string &name, const glm::vec3 &vector);
    void SetUniformVector4(const std::string &name, const glm::vec4 &vector);
    void SetUniformMatrix4(const std::string &name, const glm::mat4 &matrix);
    void SetUniformInteger(const std::string &name, std::int32_t value);
    void SetUniformIntegerArray(const std::string &name, const std::span<std::int32_t> &array);

private:
    std::uint32_t id_;
    std::unordered_map<std::string, UniformLocation> uniform_locations_;

    void Release() noexcept;
    [[nodiscard]] std::string GetInfoLog() const;
};
}  // namespace graphics