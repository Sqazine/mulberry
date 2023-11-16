#include "Shader.h"
#include "App.h"
namespace mulberry
{
    Shader::Shader(ShaderStage type, std::string_view content)
    {
        switch (AppConfig::graphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLShader = std::make_unique<GLShader>(type, content);
            break;
        default:
            mVKShader = std::make_unique<VKShader>(type, content);
            break;
        }
    }
    Shader::~Shader()
    {
        switch (AppConfig::graphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            mGLShader.reset(nullptr);
            break;
        default:
            mVKShader.reset(nullptr);
            break;
        }
    }

    const ShaderStage &Shader::Type() const
    {
        switch (AppConfig::graphicsConfig.backend)
        {
        case GraphicsBackend::GL:
            return mGLShader->Type();
        default:
            return mVKShader->Type();
        }
    }

    ShaderGroup::ShaderGroup()
        : mBackend(AppConfig::graphicsConfig.backend)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            mGLShaderGroup = std::make_unique<GLShaderGroup>();
        default:
            // TODO...
            break;
        }
    }
    ShaderGroup::~ShaderGroup()
    {
    }

    void ShaderGroup::SetActive(bool isActive)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderGroup->SetActive(isActive);
        default:
            // TODO
            break;
        }
    }

    void ShaderGroup::SetTexture(std::string_view name, const Texture *texture)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderGroup->SetTexture(name, texture->mGLTexture.get());
            break;
        default:
            // TODO
            break;
        }
    }

    void ShaderGroup::SetVertexArray(const VertexArray *vertexArray)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderGroup->SetVertexArray(vertexArray->mGLVertexArray.get());
            break;
        default:
            // TODO
            break;
        }
    }
    void ShaderGroup::ResetVertexArray()
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderGroup->ResetVertexArray();
            break;
        default:
            // TODO
            break;
        }
    }

    void ShaderGroup::ResetVertexBuffer(std::string_view name)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderGroup->ResetVertexBuffer(name);
            break;
        default:
            // TODO
            break;
        }
    }

    bool ShaderGroup::AttachShader(const Shader &shader)
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderGroup->AttachShader(*shader.mGLShader);
        default:
            // TODO
            return true;
        }
    }

    uint32_t ShaderGroup::GetAttribute(std::string_view name) const
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderGroup->GetAttribute(name);
        default:
            // TODO
            return 0;
        }
    }
    
    uint32_t ShaderGroup::GetUniform(std::string_view name) const
    {
        switch (mBackend)
        {
        case GraphicsBackend::GL:
            return mGLShaderGroup->GetUniform(name);
        default:
            // TODO
            return 0;
        }
    }
}