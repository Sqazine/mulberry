#pragma once
#include "AppGlobalConfig.h"
#include "GL/GLIndexBuffer.h"
#include "VK/VKIndexBuffer.h"

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
        std::unique_ptr<GLIndexBuffer> mGLIndexBuffer;
        std::unique_ptr<VKIndexBuffer> mVKIndexBuffer;
    };

    inline IndexBuffer::IndexBuffer()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLIndexBuffer = std::make_unique<GLIndexBuffer>();
            break;
        default:
            mVKIndexBuffer = std::make_unique<VKIndexBuffer>();
            break;
        }
    }

    template <typename T>
    inline IndexBuffer::IndexBuffer(const std::vector<T> &indices)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLIndexBuffer = std::make_unique<GLIndexBuffer>(indices);
            break;
        default:
            mVKIndexBuffer = std::make_unique<VKIndexBuffer>(indices);
            break;
        }
    }

    inline IndexBuffer::~IndexBuffer()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLIndexBuffer.reset(nullptr);
            break;
        default:
            mVKIndexBuffer.reset(nullptr);
            break;
        }
    }

    template <typename T>
    inline void IndexBuffer::Set(const std::vector<T> &input)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLIndexBuffer->Set(input);
            break;
        default:
            mVKIndexBuffer->Set(input);
            break;
        }
    }
};