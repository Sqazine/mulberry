#include "Texture.h"
#include "App.h"
#include "Texture.h"
#include "Logger.h"

namespace mulberry
{
    Texture::Texture()
    {
    }

    Texture::~Texture()
    {
    }

    Vec2 Texture::GetExtent() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetImage()->GetExtent());
    }

    Texture &Texture::SetImageData(const ImageData &data)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->SetImageData(data));
        return *this;
    }

    Texture &Texture::SetMagFilter(FilterMode filter)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->GetSampler()->SetMagFilter(filter));
        return *this;
    }

    Texture &Texture::SetMinFilter(FilterMode filter)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->GetSampler()->SetMinFilter(filter));
        return *this;
    }
    Texture &Texture::SetWrapU(WrapMode address)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->GetSampler()->SetWrapU(address));
        return *this;
    }
    Texture &Texture::SetWrapV(WrapMode address)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->GetSampler()->SetWrapV(address));
        return *this;
    }
    Texture &Texture::SetWrapW(WrapMode address)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->GetSampler()->SetWrapW(address));
        return *this;
    }
    Texture &Texture::SetAnisotropyLevel(float level)
    {
        GRAPHICS_RHI_IMPL_SWITCHER(GetVkImpl()->GetSampler()->SetAnisotropyLevel(level));
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
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetMagFilter());
    }
    const FilterMode &Texture::GetMinFilter() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetMinFilter());
    }
    const WrapMode &Texture::GetWrapModeU() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetWrapModeU());
    }
    const WrapMode &Texture::GetWrapModeV() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetWrapModeV());
    }
    const WrapMode &Texture::GetWrapModeW() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetWrapModeW());
    }

    float Texture::GetMaxAnisotropyLevel() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetMaxAnisotropyLevel());
    }

    const BorderColor &Texture::GetBorderColor() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetBorderColor());
    }

    const MipMapMode &Texture::GetMipMapMode() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetMipMapMode());
    }

    float Texture::GetMipMapBias() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetMipMapBias());
    }

    float Texture::GetMinMipMapLevel() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetMinMipMapLevel());
    }
    
    float Texture::GetMaxMipMapLevel() const
    {
        GRAPHICS_RHI_IMPL_SWITCHER(return GetVkImpl()->GetSampler()->GetMaxMipMapLevel());
    }
}