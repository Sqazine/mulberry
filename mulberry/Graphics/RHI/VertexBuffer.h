#pragma once
#include <memory>
#include "AppGlobalConfig.h"
#include "GL/GLVertexBuffer.h"
#include "VK/VKVertexBuffer.h"
namespace mulberry
{
    template <typename T>
    class VertexBuffer
    {
    public:
        VertexBuffer();
        VertexBuffer(const std::vector<T> &inputArray);
        ~VertexBuffer();

        void Set(const std::vector<T> &inputArray);

        uint32_t Size();

    private:
        friend class ShaderProgram;
        std::unique_ptr<GLVertexBuffer<T>> mGLVertexBuffer;
        std::unique_ptr<VKVertexBuffer<T>> mVKVertexBuffer;
    };

    template <typename T>
    inline VertexBuffer<T>::VertexBuffer()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLVertexBuffer = std::make_unique<GLVertexBuffer<T>>();
            break;
        default:
            mVKVertexBuffer = std::make_unique<VKVertexBuffer<T>>();
            break;
        }
    }

    template <typename T>
    inline VertexBuffer<T>::VertexBuffer(const std::vector<T> &inputArray)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLVertexBuffer = std::make_unique<GLVertexBuffer<T>>(inputArray);
            break;
        default:
            mVKVertexBuffer = std::make_unique<VKVertexBuffer<T>>(inputArray);
            break;
        }
    }

    template <typename T>
    inline VertexBuffer<T>::~VertexBuffer()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLVertexBuffer.reset(nullptr);
            break;
        default:
            mVKVertexBuffer.reset(nullptr);
            break;
        }
    }

    template <typename T>
    inline void VertexBuffer<T>::Set(const std::vector<T> &inputArray)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLVertexBuffer->Set(inputArray);
            break;
        default:
            mVKVertexBuffer->Set(inputArray);
            break;
        }
    }

    template <typename T>
    inline uint32_t VertexBuffer<T>::Size()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLVertexBuffer->Size();
        default:
            return mVKVertexBuffer->Size();
        }
    }
}