#pragma once
#include <cstdint>
#include <type_traits>
#include <vulkan/vulkan.h>
#include "RHI/Enum.h"
#include "Enum.h"
#include "Base.h"

namespace mulberry::rhi::vk
{
    class Sampler : public Base
    {
    public:
        Sampler();
        ~Sampler();

        const VkSampler &GetHandle();

        Sampler &SetMagFilter(rhi::FilterMode filter);
        Sampler &SetMinFilter(rhi::FilterMode filter);
        Sampler &SetWrapU(rhi::WrapMode address);
        Sampler &SetWrapV(rhi::WrapMode address);
        Sampler &SetWrapW(rhi::WrapMode address);
        Sampler &SetAnisotropyLevel(float level);
        Sampler &SetBorderColor(rhi::BorderColor borderColor);
        Sampler &SetMipMapMode(rhi::MipMapMode mipmapMode);
        Sampler &SetMipMapBias(float bias);
        Sampler &SetMinMipMapLevel(float level);
        Sampler &SetMaxMipMapLevel(float level);

        const rhi::FilterMode &GetMagFilter() const;
        const rhi::FilterMode &GetMinFilter() const;
        const rhi::WrapMode &GetWrapModeU() const;
        const rhi::WrapMode &GetWrapModeV() const;
        const rhi::WrapMode &GetWrapModeW() const;

        float GetMaxAnisotropyLevel() const;

        const rhi::BorderColor &GetBorderColor() const;

        const rhi::MipMapMode &GetMipMapMode() const;

        float GetMipMapBias() const;
        float GetMinMipMapLevel() const;
        float GetMaxMipMapLevel() const;

    private:
        void Build();

        VkSampler mHandle;

        bool mIsDirty{true};

        rhi::FilterMode mMagFilter{FilterMode::LINEAR};
        rhi::FilterMode mMinFilter{FilterMode::LINEAR};
        rhi::WrapMode mWrapU{WrapMode::REPEAT};
        rhi::WrapMode mWrapV{WrapMode::REPEAT};
        rhi::WrapMode mWrapW{WrapMode::REPEAT};

        float mMaxAnisotropyLevel{0};

        BorderColor mBorderColor{BorderColor::FLOAT_OPAQUE_BLACK};

        MipMapMode mMipMapMode{MipMapMode::LINEAR};
        float mMipMapBias{0.0f};
        float mMinMipMapLevel{0.0f};
        float mMaxMipMapLevel{0.0f};
    };
}