#pragma once
#include <string_view>
#include <memory>
#include <vector>
#include "GraphicsContext.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "GL/GLShader.h"
#include "VK/VKShader.h"

namespace mulberry
{
    enum ShaderStage
    {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        TESSELLATION_CONTROL,
        TESSELLATION_EVAL,
        COMPUTE,
    };

    class Shader
    {
    public:
        Shader(ShaderStage type, std::string_view content);
        ~Shader();

        const ShaderStage &Type() const;

    private:
        friend class ShaderGroup;

        std::unique_ptr<class GLShader> mGLShader;
        std::unique_ptr<class VKShader> mVKShader;
    };

    class ShaderGroup
    {
    public:
        ShaderGroup();
        ~ShaderGroup();

        void SetActive(bool isActive);

        template <typename T>
        void SetUniformValue(std::string_view name, T value);

        template <typename T>
        void SetUniformArray(std::string_view name, const std::vector<T> &valueArray);

        void SetTexture(std::string_view name, const Texture *texture);

        void SetVertexArray(const VertexArray *vertexArray);
        void ResetVertexArray();

        template <typename T>
        void SetVertexBuffer(std::string_view name, const VertexBuffer<T> *vertexBuffer);
        void ResetVertexBuffer(std::string_view name);

        bool AttachShader(const Shader &shader);

        uint32_t GetAttribute(std::string_view name) const;
        uint32_t GetUniform(std::string_view name) const;

    private:
        GraphicsBackend mBackend;
        std::unique_ptr<class GLShaderGroup> mGLShaderGroup;
    };

    template <typename T>
    inline void ShaderGroup::SetUniformValue(std::string_view name, T value)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            mGLShaderGroup->SetUniformValue<T>(name, value);
        default:
            // TODO
            break;
        }
    }

    template <typename T>
    inline void ShaderGroup::SetUniformArray(std::string_view name, const std::vector<T> &valueArray)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            mGLShaderGroup->SetUniformArray<T>(name, valueArray);
        default:
            // TODO
            break;
        }
    }

    template <typename T>
    inline void ShaderGroup::SetVertexBuffer(std::string_view name, const VertexBuffer<T> *vertexBuffer)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            mGLShaderGroup->SetVertexBuffer<T>(name, vertexBuffer->mGLVertexBuffer.get());
        default:
            // TODO
            break;
        }
    }
}