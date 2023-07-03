#pragma once

#include <cstdint>

#include "graphics/vertex_buffer.h"

namespace graphics {
class VertexArray {
public:
    enum class DataType : std::uint32_t {
        kByte          = 0x1400,
        kUnsignedByte  = 0x1401,
        kShort         = 0x1402,
        kUnsignedShort = 0x1403,
        kInt           = 0x1404,
        kUnsignedInt   = 0x1405,
        kFloat         = 0x1406,
        kDouble        = 0x140A
    };

    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray &)            = delete;
    VertexArray &operator=(const VertexArray &) = delete;

    VertexArray(VertexArray &&other) noexcept;
    VertexArray &operator=(VertexArray &&other) noexcept;

    void Bind() const noexcept;
    static void Unbind() noexcept;

    void SetElementBuffer(const VertexBuffer &buffer) const noexcept;
    void BindAttribute(const VertexBuffer &buffer, std::uint32_t index, std::int32_t size, DataType type,
                       std::int32_t stride, std::int32_t offset) const noexcept;

private:
    std::uint32_t id_;

    void Release() noexcept;
};
}  // namespace graphics