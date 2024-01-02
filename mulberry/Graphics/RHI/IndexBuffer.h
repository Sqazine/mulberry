#pragma once
#include "Utils.h"
#include "AppConfig.h"
#include "VK/Buffer.h"

namespace mulberry
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
        switch (AppConfig::graphicsConfig.backend)
        {
        case GraphicsBackend::VK:
            mGLIndexBuffer = std::make_unique<GLIndexBuffer>(indices);
            break;
        default:
            mIndexBuffer = std::make_unique<IndexBuffer>(indices);
            break;
        }
    }

    inline IndexBuffer::~IndexBuffer()
    {
        switch (AppConfig::graphicsConfig.backend)
        {
        case GraphicsBackend::VK:
            mGLIndexBuffer.reset(nullptr);
            break;
        default:
            mIndexBuffer.reset(nullptr);
            break;
        }
    }

    template <typename T>
    inline void IndexBuffer::Set(const std::vector<T> &input)
    {
        switch (AppConfig::graphicsConfig.backend)
        {
        case GraphicsBackend::VK:
            mGLIndexBuffer->Set(input);
            break;
        default:
            mIndexBuffer->Set(input);
            break;
        }
    }
};