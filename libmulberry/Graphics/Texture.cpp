#include "Texture.h"
#include "App.h"
#include "GL/GLTexture.h"

namespace mulberry
{
    Texture::Texture()
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLTexture = std::make_unique<GLTexture>();
            break;
        default:
            //TODO...
            //mVKTexture=std::make_unique<VKTexture>();
            break;
        }
    }
    Texture::Texture(const TextureInfo &info)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLTexture = std::make_unique<GLTexture>(info);
            break;
        default:
            break;
        }
    }
    Texture::~Texture()
    {
        mGLTexture.reset(nullptr);
    }

    void Texture::CreateFrom(const TextureInfo &info)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLTexture->CreateFrom(info);
            break;
        default:
            break;
        }
    }
    void Texture::CreateFromSurface(SDL_Surface *surface)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLTexture->CreateFromSurface(surface);
            break;
        default:
            break;
        }
    }

    const TextureInfo &Texture::GetCreateInfo() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLTexture->GetCreateInfo();
        default:
            break;
        }
    }
}