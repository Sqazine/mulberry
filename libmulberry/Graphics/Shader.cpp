#include "Shader.h"
#include "GL/GLShader.h"
#include "App.h"
namespace mulberry
{
    ShaderModule::ShaderModule(ShaderType type, std::string_view content)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLShaderModule = std::make_unique<GLShaderModule>(type, content);
            break;
        default:
            break;
        }
    }
    ShaderModule::~ShaderModule()
    {
    }

    const ShaderType &ShaderModule::Type() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLShaderModule->Type();
        default:
            break;
        }
    }

    ShaderProgram::ShaderProgram()
        : mBackend(App::GetInstance().GetGraphicsConfig().backend)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            mGLShaderProgram = std::make_unique<GLShaderProgram>();
        default:
            // TODO...
            break;
        }
    }
    ShaderProgram::~ShaderProgram()
    {
    }

    void ShaderProgram::SetActive(bool isActive)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderProgram->SetActive(isActive);
        default:
            break;
        }
    }

    void ShaderProgram::SetTexture(std::string_view name, const Texture *texture)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderProgram->SetTexture(name, texture->mGLTexture.get());
            break;
        }
    }

    bool ShaderProgram::AttachShader(const ShaderModule &shader)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderProgram->AttachShader(*shader.mGLShaderModule);
        default:
            break;
        }
    }

    uint32_t ShaderProgram::GetAttribute(std::string_view name) const
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderProgram->GetAttribute(name);
        default:
            break;
        }
    }
    uint32_t ShaderProgram::GetUniform(std::string_view name) const
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderProgram->GetUniform(name);
        default:
            break;
        }
    }
}