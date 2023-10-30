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
            // TODO...
            // mVKTexture=std::make_unique<VKTexture>();
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
            // TODO
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
            // TODO
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
            // TODO
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
            // TODO
            break;
        }
    }

    uint32_t Texture::GetWidth() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLTexture->GetCreateInfo().data.width;
        default:
            // TODO
            break;
        }
    }
    uint32_t Texture::GetHeight() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLTexture->GetCreateInfo().data.height;
        default:
            // TODO
            break;
        }
    }

    Vec2 Texture::GetExtent() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return Vec2(mGLTexture->GetCreateInfo().data.width, mGLTexture->GetCreateInfo().data.height);
        default:
            // TODO
            break;
        }
    }
}