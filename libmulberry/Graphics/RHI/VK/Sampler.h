#pragma once
#include <cstdint>
#include <type_traits>
#include <vulkan/vulkan.h>
#include "RHI/Enum.h"
#include "Enum.h"
#include "Base.h"

namespace mulberry::vk
{
    class Sampler : public Base
    {
    public:
        Sampler();
        ~Sampler();

        const VkSampler &GetHandle();

        Sampler &SetMagFilter(FilterMode filter);
        Sampler &SetMinFilter(FilterMode filter);
        Sampler &SetWrapU(WrapMode address);
        Sampler &SetWrapV(WrapMode address);
        Sampler &SetWrapW(WrapMode address);
        Sampler &SetAnisotropyLevel(float level);
        Sampler &SetBorderColor(BorderColor borderColor);
        Sampler &SetMipMapMode(MipMapMode mipmapMode);
        Sampler &SetMipMapBias(float bias);
        Sampler &SetMinMipMapLevel(float level);
        Sampler &SetMaxMipMapLevel(float level);

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

    private:
        void Build();

        VkSampler mHandle;

        bool mIsDirty{true};

        FilterMode mMagFilter{FilterMode::LINEAR};
        FilterMode mMinFilter{FilterMode::LINEAR};
        WrapMode mWrapU{WrapMode::REPEAT};
        WrapMode mWrapV{WrapMode::REPEAT};
        WrapMode mWrapW{WrapMode::REPEAT};

        float mMaxAnisotropyLevel{0};

        BorderColor mBorderColor{BorderColor::FLOAT_OPAQUE_BLACK};

        MipMapMode mMipMapMode{MipMapMode::LINEAR};
        float mMipMapBias{0.0f};
        float mMinMipMapLevel{0.0f};
        float mMaxMipMapLevel{0.0f};
    };
}