#include "Texture.h"
#include "RenderContext.h"
#include "RenderContextInfo.h"
namespace Pe2
{

    Texture::Texture(const TextureInfo &info)
        : m_GLTexture(nullptr)
    {
        switch (RenderContext::GetRenderBackend())
        {
        case RenderBackend::GL:
            m_GLTexture = std::make_unique<GL::Texture>(info);
            break;

        default:
            m_GLTexture = std::make_unique<GL::Texture>(info);
            break;
        }
    }
    Texture::~Texture()
    {
    }

}