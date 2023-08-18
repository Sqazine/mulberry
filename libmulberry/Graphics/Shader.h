#pragma once
#include <string_view>
#include <memory>
#include <vector>
#include "GraphicsContext.h"
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
            break;
        }
    }

    template <typename T>
    inline void ShaderProgram::SetUniformArray(std::string_view name, const std::vector<T> &valueArray)
    {
        switch (App::GetInstance().GetGraphicsConfig())
        {
        case GraphicsBackend::GL:
            mGLShaderProgram->SetUniformValue<T>(name, valueArray);
        default:
            break;
        }
    }
}