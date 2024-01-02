#include "Sampler.h"
#include "Device.h"
#include "Utils.h"
#include "Logger.h"

namespace mulberry::vk
{
    Sampler::Sampler()
        :mHandle(VK_NULL_HANDLE)
    {
    }

    Sampler::~Sampler()
    {
        if (mHandle)
            vkDestroySampler(mDevice.GetHandle(), mHandle, nullptr);
    }

    const VkSampler &Sampler::GetHandle()
    {
        if (mHandle == VK_NULL_HANDLE || mIsDirty)
            Build();
        return mHandle;
    }

    Sampler &Sampler::SetMagFilter(FilterMode filter)
    {
        SET(mMagFilter, filter);
    }
    Sampler &Sampler::SetMinFilter(FilterMode filter)
    {
        SET(mMinFilter, filter);
    }
    Sampler &Sampler::SetWrapU(WrapMode address)
    {
        SET(mWrapU, address);
    }
    Sampler &Sampler::SetWrapV(WrapMode address)
    {
        SET(mWrapV, address);
    }
    Sampler &Sampler::SetWrapW(WrapMode address)
    {
        SET(mWrapW, address);
    }
    Sampler &Sampler::SetAnisotropyLevel(float level)
    {
        SET(mMaxAnisotropyLevel, level);
    }
    Sampler &Sampler::SetBorderColor(BorderColor borderColor)
    {
        SET(mBorderColor, borderColor);
    }
    Sampler &Sampler::SetMipMapMode(MipMapMode mipmapMode)
    {
        SET(mMipMapMode, mipmapMode);
    }
    Sampler &Sampler::SetMipMapBias(float bias)
    {
        SET(mMipMapBias, bias);
    }
    Sampler &Sampler::SetMinMipMapLevel(float level)
    {
        SET(mMinMipMapLevel, level);
    }
    Sampler &Sampler::SetMaxMipMapLevel(float level)
    {
        SET(mMaxMipMapLevel, level);
    }

    const FilterMode &Sampler::GetMagFilter() const
    {
        return mMagFilter;
    }
    const FilterMode &Sampler::GetMinFilter() const
    {
        return mMinFilter;
    }
    const WrapMode &Sampler::GetWrapModeU() const
    {
        return mWrapU;
    }
    const WrapMode &Sampler::GetWrapModeV() const
    {
        return mWrapV;
    }
    const WrapMode &Sampler::GetWrapModeW() const
    {
        return mWrapW;
    }

    float Sampler::GetMaxAnisotropyLevel() const
    {
        return mMaxAnisotropyLevel;
    }

    const BorderColor &Sampler::GetBorderColor() const
    {
        return mBorderColor;
    }

    const MipMapMode &Sampler::GetMipMapMode() const
    {
        return mMipMapMode;
    }

    float Sampler::GetMipMapBias() const
    {
        return mMipMapBias;
    }
    float Sampler::GetMinMipMapLevel() const
    {
        return mMinMipMapLevel;
    }
    float Sampler::GetMaxMipMapLevel() const
    {
        return mMaxMipMapLevel;
    }

    void Sampler::Build()
    {
        VkSamplerCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        info.magFilter = FILTER_MODE_CAST(mMagFilter);
        info.minFilter = FILTER_MODE_CAST(mMinFilter);
        info.addressModeU = WRAP_MODE_CAST(mWrapU);
        info.addressModeV = WRAP_MODE_CAST(mWrapV);
        info.addressModeW = WRAP_MODE_CAST(mWrapW);
        info.anisotropyEnable = mMaxAnisotropyLevel > 0 ? VK_TRUE : VK_FALSE;
        info.maxAnisotropy = mMaxAnisotropyLevel;
        info.borderColor = BORDER_COLOR_CAST(mBorderColor);
        info.unnormalizedCoordinates = VK_FALSE;
        info.compareEnable = VK_FALSE;
        info.compareOp = VK_COMPARE_OP_ALWAYS;
        info.mipmapMode = MIPMAP_MODE_CAST(mMipMapMode);
        info.mipLodBias = mMipMapBias;
        info.minLod = mMinMipMapLevel;
        info.maxLod = mMaxMipMapLevel;

        VK_CHECK(vkCreateSampler(mDevice.GetHandle(), &info, nullptr, &mHandle));
        mIsDirty = false;
    }
}