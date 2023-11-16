#pragma once
#include <memory>
#include "AppConfig.h"
#include "GL/GLVertexArray.h"
namespace mulberry
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

    private:
        friend class ShaderProgram;
        std::unique_ptr<GLVertexArray> mGLVertexArray;
    };

    inline VertexArray::VertexArray()
    {
        switch (AppConfig::graphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLVertexArray = std::make_unique<GLVertexArray>();
            break;
        default:
            // TODO
            break;
        }
    }
    inline VertexArray::~VertexArray()
    {
    }
}