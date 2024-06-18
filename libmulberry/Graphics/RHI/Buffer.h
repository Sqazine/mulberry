#pragma once
#include <memory>
#include "Defs.h"
#include "Utils.h"
#include "AppConfig.h"
#include "Graphics/GraphicsConfig.h"
#include "Graphics/RHI/VK/Buffer.h"
namespace mulberry
{
    class VertexBuffer : GRAPHICS_RHI_IMPL_DECL(VertexBuffer)
    {
    public:
        VertexBuffer() {}
        template <typename T>
        VertexBuffer(const std::vector<T> &input) : Base(input) {}
        ~VertexBuffer() {}

        template <typename T>
        void Fill(const std::vector<T> &input)
        {
            GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->Fill(input));
        }

        uint64_t GetSize()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSize());
        }
    };

    class IndexBuffer : GRAPHICS_RHI_IMPL_DECL(IndexBuffer)
    {
    public:
        IndexBuffer() {}
        template <typename T>
        IndexBuffer(const std::vector<T> &indices) : Base(indices) {}
        ~IndexBuffer() {}

        template <typename T>
        void Fill(const std::vector<T> &input)
        {
            GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->Fill(input));
        }

        uint32_t GetSize()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSize());
        }
    };
}