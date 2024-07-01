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

namespace mulberry
{
    struct Texture
    {
    public:
        virtual ~Texture() = default;

        static Texture* Create();
        static std::unique_ptr<Texture> CreateUnique();

        virtual Texture *SetImageData(const ImageData &data) = 0;
        virtual Texture *SetMagFilter(FilterMode filter) = 0;
        virtual Texture *SetMinFilter(FilterMode filter) = 0;
        virtual Texture *SetWrapU(WrapMode address) = 0;
        virtual Texture *SetWrapV(WrapMode address) = 0;
        virtual Texture *SetWrapW(WrapMode address) = 0;
        virtual Texture *SetAnisotropyLevel(float level) = 0;
        virtual Texture *SetBorderColor(BorderColor borderColor) = 0;
        virtual Texture *SetMipMapMode(MipMapMode mipmapMode) = 0;
        virtual Texture *SetMipMapBias(float bias) = 0;
        virtual Texture *SetMinMipMapLevel(float level) = 0;
        virtual Texture *SetMaxMipMapLevel(float level) = 0;

        virtual FilterMode GetMagFilter() const = 0;
        virtual FilterMode GetMinFilter() const = 0;
        virtual WrapMode GetWrapModeU() const = 0;
        virtual WrapMode GetWrapModeV() const = 0;
        virtual WrapMode GetWrapModeW() const = 0;
        virtual float GetMaxAnisotropyLevel() const = 0;
        virtual BorderColor GetBorderColor() const = 0;
        virtual MipMapMode GetMipMapMode() const = 0;
        virtual float GetMipMapBias() const = 0;
        virtual float GetMinMipMapLevel() const = 0;
        virtual float GetMaxMipMapLevel() const = 0;

        virtual Vec2 GetExtent() const = 0;

    protected:
        Texture() = default;
    };
}