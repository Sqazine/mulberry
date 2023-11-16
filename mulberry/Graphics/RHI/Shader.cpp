#include "Shader.h"
#include "App.h"
namespace mulberry
{
    ShaderModule::ShaderModule(ShaderStage type, std::string_view content)
    {
        switch (AppConfig::graphicsConfig.backend)
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
        switch (AppConfig::graphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLShaderModule.reset(nullptr);
            break;
        default:
            mVKShaderModule.reset(nullptr);
            break;
        }
    }

    const ShaderStage &ShaderModule::Type() const
    {
        switch (AppConfig::graphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLShaderModule->Type();
        default:
            return mVKShaderModule->Type();
        }
    }

    ShaderProgram::ShaderProgram()
        : mBackend(AppConfig::graphicsConfig.backend)
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
            return true;
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
            return 0;
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
            return 0;
        }
    }
}