#pragma once
#include "Utils.h"
#include "AppConfig.h"
#include "VK/Buffer.h"

namespace mulberry::rhi
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        template <typename T>
        IndexBuffer(const std::vector<T> &indices);
        ~IndexBuffer();

        template <typename T>
        void Set(const std::vector<T> &input);

    private:
        friend class RasterPipeline;
        std::unique_ptr<vk::IndexBuffer> mVKIndexBufferImpl;
    };

    inline IndexBuffer::IndexBuffer()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKIndexBufferImpl=std::make_unique<vk::IndexBuffer>());
    }

    template <typename T>
    inline IndexBuffer::IndexBuffer(const std::vector<T> &indices)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKIndexBufferImpl=std::make_unique<vk::IndexBuffer>(indices));
    }

    inline IndexBuffer::~IndexBuffer()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKIndexBufferImpl.reset(nullptr));
    }

    template <typename T>
    inline void IndexBuffer::Set(const std::vector<T> &input)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKIndexBufferImpl->Set(input));
    }
};