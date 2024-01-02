#include "Texture.h"
#include "App.h"
#include "VK/Texture.h"
#include "Logger.h"

namespace mulberry
{
    Texture::Texture()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKTextureImpl = std::make_unique<vk::Texture>());
    }

    Texture::~Texture()
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKTextureImpl.reset(nullptr));
    }

    uint32_t Texture::GetWidth() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetImage()->GetWidth());
    }
    uint32_t Texture::GetHeight() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetImage()->GetHeight());
    }

    Vec2 Texture::GetExtent() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetImage()->GetExtent());
    }
}