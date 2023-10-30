#include "Shader.h"
#include "GL/GLShader.h"
#include "VK/VKShader.h"
#include "App.h"
namespace mulberry
{
    ShaderModule::ShaderModule(ShaderType type, std::string_view content)
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLShaderModule = std::make_unique<GLShaderModule>(type, content);
            break;
        default:
            mVKShaderModule = std::make_unique<VKShaderModule>(type, content);
            break;
        }
    }
    ShaderModule::~ShaderModule()
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLShaderModule.reset(nullptr);
            break;
        default:
            mVKShaderModule.reset(nullptr);
            break;
        }
    }

    const ShaderType &ShaderModule::Type() const
    {
        switch (AppGlobalConfig::gGraphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLShaderModule->Type();
        default:
            return mVKShaderModule->Type();
        }
    }

    ShaderProgram::ShaderProgram()
        : mBackend(AppGlobalConfig::gGraphicsConfig.backend)
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
            // TODO
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
        default:
            // TODO
            break;
        }
    }

    void ShaderProgram::SetVertexArray(const VertexArray *vertexArray)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderProgram->SetVertexArray(vertexArray->mGLVertexArray.get());
            break;
        default:
            // TODO
            break;
        }
    }
    void ShaderProgram::ResetVertexArray()
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderProgram->ResetVertexArray();
            break;
        default:
            // TODO
            break;
        }
    }

    void ShaderProgram::ResetVertexBuffer(std::string_view name)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderProgram->ResetVertexBuffer(name);
            break;
        default:
            // TODO
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
            // TODO
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
            // TODO
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
            // TODO
            break;
        }
    }
}