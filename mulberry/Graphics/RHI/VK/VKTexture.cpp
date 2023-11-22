#include "VKTexture.h"
#include "VKDevice.h"
#include "VKContext.h"
#include "App.h"
#include "Logger.h"
namespace mulberry
{
    VKTexture::VKTexture()
    
    {
    }

    VKTexture::VKTexture(VkImage rawImage, VkFormat format)
        : mImage(std::make_unique<VKImage>(rawImage, format)), mImageView(std::make_unique<VKImageView>(rawImage, format, VK_IMAGE_VIEW_TYPE_2D, ImageAspect::COLOR))
    {
    }

    VKTexture::VKTexture(const TextureInfo &info)
        : mInfo(info)
    {
        VkSamplerCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        createInfo.magFilter = ToVkFilter(info.magFilter);
        createInfo.minFilter = ToVkFilter(info.minFilter);
        createInfo.addressModeU = ToVkWrapMode(info.wrapS);
        createInfo.addressModeV = ToVkWrapMode(info.wrapT);

        VK_CHECK(vkCreateSampler(RAW_VK_DEVICE_HANDLE, &createInfo, nullptr, &mSampler));
    }
    VKTexture::~VKTexture()
    {
        if (mSampler)
            vkDestroySampler(RAW_VK_DEVICE_HANDLE, mSampler, nullptr);
    }

    void VKTexture::CreateFrom(const TextureInfo &info)
    {
    }
    void VKTexture::CreateFromSurface(SDL_Surface *surface)
    {
    }

    const VKImage *VKTexture::GetHandle() const
    {
        return mImage.get();
    }

    const VKImageView *VKTexture::GetView() const
    {
        return mImageView.get();
    }

    const TextureInfo &VKTexture::GetCreateInfo() const
    {
        return mInfo;
    }

    VkFilter VKTexture::ToVkFilter(FilterMode mode)
    {
        switch (mode)
        {
        case FilterMode::LINEAR:
            return VK_FILTER_LINEAR;
        default:
            return VK_FILTER_NEAREST;
        }
    }
    VkSamplerAddressMode VKTexture::ToVkWrapMode(WrapMode mode)
    {
        switch (mode)
        {
        case WrapMode::REPEAT:
            return VK_SAMPLER_ADDRESS_MODE_REPEAT;
        case WrapMode::MIRROR_REPEAT:
            return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
        case WrapMode::CLAMP_TO_EDGE:
            return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        case WrapMode::CLAMP_TO_BORDER:
            return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
        default:
            return VK_SAMPLER_ADDRESS_MODE_REPEAT;
        }
    }
}