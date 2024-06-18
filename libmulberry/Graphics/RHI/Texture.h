#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include "Core/AssetManager.h"
#include "Core/Tools.h"
#include "Defs.h"
#include "Color.h"
#include "Format.h"
#include "Math/Vec2.h"
#include "Graphics/RHI/VK/Texture.h"

namespace mulberry
{
    struct Texture : GRAPHICS_RHI_IMPL_DECL(Texture)
    {
    public:
        Texture();
        ~Texture();

        Texture &SetImageData(const ImageData &data);
        Texture &SetMagFilter(FilterMode filter);
        Texture &SetMinFilter(FilterMode filter);
        Texture &SetWrapU(WrapMode address);
        Texture &SetWrapV(WrapMode address);
        Texture &SetWrapW(WrapMode address);
        Texture &SetAnisotropyLevel(float level);
        Texture &SetBorderColor(BorderColor borderColor);
        Texture &SetMipMapMode(MipMapMode mipmapMode);
        Texture &SetMipMapBias(float bias);
        Texture &SetMinMipMapLevel(float level);
        Texture &SetMaxMipMapLevel(float level);

        const FilterMode &GetMagFilter() const;
        const FilterMode &GetMinFilter() const;
        const WrapMode &GetWrapModeU() const;
        const WrapMode &GetWrapModeV() const;
        const WrapMode &GetWrapModeW() const;

        float GetMaxAnisotropyLevel() const;

        const BorderColor &GetBorderColor() const;

        const MipMapMode &GetMipMapMode() const;

        float GetMipMapBias() const;
        float GetMinMipMapLevel() const;
        float GetMaxMipMapLevel() const;

        Vec2 GetExtent() const;
    };
}