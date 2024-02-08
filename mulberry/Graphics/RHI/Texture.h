#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <SDL.h>
#include "Color.h"
#include "Math/Vec2.h"
#include "Core/AssetManager.h"
#include "Format.h"
#include "Enum.h"
#include "VK/Texture.h"

namespace mulberry::rhi
{
    struct Texture
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

    private:
        friend class RasterShaderGroup;
        friend class RasterPass;
        std::unique_ptr<vk::Texture> mVKTextureImpl;
    };
}