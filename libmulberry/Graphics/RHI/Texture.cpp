#include "Texture.h"
#include "App.h"
#include "GL/GLTexture.h"
#include "VK/VKTexture.h"

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
            mVKTexture = std::make_unique<VKTexture>();
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
            mVKTexture = std::make_unique<VKTexture>(info);
            break;
        }
    }
    Texture::~Texture()
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLTexture .reset(nullptr);
            break;
        default:
            mVKTexture.reset(nullptr);
            break;
        }   
    }

    void Texture::CreateFrom(const TextureInfo &info)
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            mGLTexture->CreateFrom(info);
            break;
        default:
            mVKTexture->CreateFrom(info);
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
             mVKTexture->CreateFromSurface(surface);
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
             return mVKTexture->GetCreateInfo();
        }
    }

    uint32_t Texture::GetWidth() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLTexture->GetCreateInfo().data.width;
        default:
            return mVKTexture->GetCreateInfo().data.width;
        }
    }
    uint32_t Texture::GetHeight() const
    {
        switch (App::GetInstance().GetGraphicsConfig().backend)
        {
        case GraphicsBackend::GL:
            return mGLTexture->GetCreateInfo().data.height;
        default:
               return mVKTexture->GetCreateInfo().data.height;
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
            return Vec2(mVKTexture->GetCreateInfo().data.width, mVKTexture->GetCreateInfo().data.height);
        }
    }
}