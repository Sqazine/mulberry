#pragma once
#include <memory>
#include "Utils.h"
#include "AppConfig.h"
#include "RHI/VK/Buffer.h"
namespace mulberry::rhi
{
    class VertexBuffer
    {
    public:
        VertexBuffer()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(mVKVertexBufferImpl = std::make_unique<vk::VertexBuffer>());
        }

        template <typename T>
        VertexBuffer(const std::vector<T> &input)
        {
            GRAPHICS_RHI_IMPL_SWITCHER(mVKVertexBufferImpl = std::make_unique<vk::VertexBuffer>(input));
        }

        ~VertexBuffer()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(mVKVertexBufferImpl.reset(nullptr));
        }

        template <typename T>
        void Fill(const std::vector<T> & input)
        {
            GRAPHICS_RHI_IMPL_SWITCHER(mVKVertexBufferImpl->Fill(input));
        }

        uint64_t Size()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(return mVKVertexBufferImpl->Size());
        }

    private:
        friend class RasterShaderGroup;
        std::unique_ptr<vk::VertexBuffer> mVKVertexBufferImpl;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(mVKIndexBufferImpl=std::make_unique<vk::IndexBuffer>());
        }

        template <typename T>
        IndexBuffer(const std::vector<T> &indices)
		{
			GRAPHICS_RHI_IMPL_SWITCHER(mVKIndexBufferImpl = std::make_unique<vk::IndexBuffer>(indices));
		}

        ~IndexBuffer()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(mVKIndexBufferImpl.reset(nullptr));
        }

        template <typename T>
        void Fill(const std::vector<T>& input)
        {
            GRAPHICS_RHI_IMPL_SWITCHER(mVKIndexBufferImpl->Fill(input));
        }

        uint32_t Size()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(return mVKIndexBufferImpl->Size());
        }

    private:
        friend class RasterShaderGroup;
        std::unique_ptr<vk::IndexBuffer> mVKIndexBufferImpl;
    };
}