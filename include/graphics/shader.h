#pragma once

#include <cstdint>
#include <stdexcept>

#include "graphics/shader_exception.h"

namespace graphics {
class ShaderCompilationException : public ShaderException {
public:
    explicit ShaderCompilationException(const std::string &arg) : ShaderException {arg} {}
};

class Shader {
public:
    enum class Type : std::uint32_t { kVertex = 0x8B31, kFragment = 0x8B30, kGeometry = 0x8DD };

    explicit Shader(Type type);
    Shader(Type type, const std::string &source);
    ~Shader();

    Shader(const Shader &)            = delete;
    Shader &operator=(const Shader &) = delete;

    Shader(Shader &&other) noexcept;
    Shader &operator=(Shader &&other) noexcept;

    void SetSource(const std::string &source) const;
    void Compile() const;

    [[nodiscard]] std::uint32_t GetId() const noexcept;

private:
    std::uint32_t id_;

    void Release() noexcept;
    [[nodiscard]] std::string GetInfoLog() const;
};
}  // namespace graphics