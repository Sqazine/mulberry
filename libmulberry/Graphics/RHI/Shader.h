#pragma once
#include <string_view>
#include <memory>
#include <vector>
#include "GraphicsContext.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "GL/GLShader.h"

namespace mulberry
{
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        TESSELLATION_CONTROL,
        TESSELLATION_EVAL,
        COMPUTE,
    };

    class ShaderModule
    {
    public:
        ShaderModule(ShaderType type, std::string_view content);
        ~ShaderModule();

        const ShaderType &Type() const;

    private:
        friend class ShaderProgram;

        std::unique_ptr<class GLShaderModule> mGLShaderModule;
        std::unique_ptr<class VKShaderModule> mVKShaderModule;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram();
        ~ShaderProgram();

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

        bool AttachShader(const ShaderModule &shader);

        uint32_t GetAttribute(std::string_view name) const;
        uint32_t GetUniform(std::string_view name) const;

    private:
        GraphicsBackend mBackend;
        std::unique_ptr<class GLShaderProgram> mGLShaderProgram;
    };

    template <typename T>
    inline void ShaderProgram::SetUniformValue(std::string_view name, T value)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            mGLShaderProgram->SetUniformValue<T>(name, value);
        default:
// TODO
            break;
        }
    }

    template <typename T>
    inline void ShaderProgram::SetUniformArray(std::string_view name, const std::vector<T> &valueArray)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            mGLShaderProgram->SetUniformArray<T>(name, valueArray);
        default:
// TODO
            break;
        }
    }

    template <typename T>
    inline void ShaderProgram::SetVertexBuffer(std::string_view name, const VertexBuffer<T> *vertexBuffer)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            mGLShaderProgram->SetVertexBuffer<T>(name, vertexBuffer->mGLVertexBuffer.get());
        default:
// TODO
            break;
        }
    }
}