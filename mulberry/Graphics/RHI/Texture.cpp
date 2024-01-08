#include "Texture.h"
#include "App.h"
#include "Texture.h"
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

    Vec2 Texture::GetExtent() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetImage()->GetExtent());
    }

    Texture &Texture::SetImageData(const ImageData &data)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKTextureImpl->SetImageData(data));
        return *this;
    }

    Texture &Texture::SetMagFilter(FilterMode filter)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKTextureImpl->GetSampler()->SetMagFilter(filter));
        return *this;
    }

    Texture &Texture::SetMinFilter(FilterMode filter)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKTextureImpl->GetSampler()->SetMinFilter(filter));
        return *this;
    }
    Texture &Texture::SetWrapU(WrapMode address)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKTextureImpl->GetSampler()->SetWrapU(address));
        return *this;
    }
    Texture &Texture::SetWrapV(WrapMode address)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKTextureImpl->GetSampler()->SetWrapV(address));
        return *this;
    }
    Texture &Texture::SetWrapW(WrapMode address)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKTextureImpl->GetSampler()->SetWrapW(address));
        return *this;
    }
    Texture &Texture::SetAnisotropyLevel(float level)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(mVKTextureImpl->GetSampler()->SetAnisotropyLevel(level));
        return *this;
    }
    Texture &Texture::SetBorderColor(BorderColor borderColor)
    {
        return *this;
    }
    Texture &Texture::SetMipMapMode(MipMapMode mipmapMode)
    {
        return *this;
    }
    Texture &Texture::SetMipMapBias(float bias)
    {
        return *this;
    }
    Texture &Texture::SetMinMipMapLevel(float level)
    {
        return *this;
    }
    Texture &Texture::SetMaxMipMapLevel(float level)
    {
        return *this;
    }

    const FilterMode &Texture::GetMagFilter() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetMagFilter());
    }
    const FilterMode &Texture::GetMinFilter() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetMinFilter());
    }
    const WrapMode &Texture::GetWrapModeU() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetWrapModeU());
    }
    const WrapMode &Texture::GetWrapModeV() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetWrapModeV());
    }
    const WrapMode &Texture::GetWrapModeW() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetWrapModeW());
    }

    float Texture::GetMaxAnisotropyLevel() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetMaxAnisotropyLevel());
    }

    const BorderColor &Texture::GetBorderColor() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetBorderColor());
    }

    const MipMapMode &Texture::GetMipMapMode() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetMipMapMode());
    }

    float Texture::GetMipMapBias() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetMipMapBias());
    }
    float Texture::GetMinMipMapLevel() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetMinMipMapLevel());
    }
    float Texture::GetMaxMipMapLevel() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return mVKTextureImpl->GetSampler()->GetMaxMipMapLevel());
    }
}