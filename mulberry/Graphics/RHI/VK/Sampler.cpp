#include "Sampler.h"
#include "Device.h"
#include "Utils.h"
#include "Logger.h"
#include "Utils.h"

namespace mulberry::rhi::vk
{
    Sampler::Sampler()
        : mHandle(VK_NULL_HANDLE)
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

    Sampler &Sampler::SetMagFilter(rhi::FilterMode filter)
    {
        SET(mMagFilter, filter);
    }
    Sampler &Sampler::SetMinFilter(rhi::FilterMode filter)
    {
        SET(mMinFilter, filter);
    }
    Sampler &Sampler::SetWrapU(rhi::WrapMode address)
    {
        SET(mWrapU, address);
    }
    Sampler &Sampler::SetWrapV(rhi::WrapMode address)
    {
        SET(mWrapV, address);
    }
    Sampler &Sampler::SetWrapW(rhi::WrapMode address)
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

    const rhi::FilterMode &Sampler::GetMagFilter() const
    {
        return mMagFilter;
    }
    const rhi::FilterMode &Sampler::GetMinFilter() const
    {
        return mMinFilter;
    }
    const rhi::WrapMode &Sampler::GetWrapModeU() const
    {
        return mWrapU;
    }
    const rhi::WrapMode &Sampler::GetWrapModeV() const
    {
        return mWrapV;
    }
    const rhi::WrapMode &Sampler::GetWrapModeW() const
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
        info.magFilter = ToVkFilterMode(mMagFilter);
        info.minFilter = ToVkFilterMode(mMinFilter);
        info.addressModeU = ToVkWrapMode(mWrapU);
        info.addressModeV = ToVkWrapMode(mWrapV);
        info.addressModeW = ToVkWrapMode(mWrapW);
        info.anisotropyEnable = mMaxAnisotropyLevel > 0 ? VK_TRUE : VK_FALSE;
        info.maxAnisotropy = mMaxAnisotropyLevel;
        info.borderColor = ToVkBorderColor(mBorderColor);
        info.unnormalizedCoordinates = VK_FALSE;
        info.compareEnable = VK_FALSE;
        info.compareOp = VK_COMPARE_OP_ALWAYS;
        info.mipmapMode = ToVkMipMapMode(mMipMapMode);
        info.mipLodBias = mMipMapBias;
        info.minLod = mMinMipMapLevel;
        info.maxLod = mMaxMipMapLevel;

        VK_CHECK(vkCreateSampler(mDevice.GetHandle(), &info, nullptr, &mHandle));
        mIsDirty = false;
    }
}