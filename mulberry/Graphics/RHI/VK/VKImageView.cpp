#include "VKImageView.h"
#include "VKDevice.h"
#include "VKUtils.h"
#include "Logger.h"
#include "VKContext.h"
#include "App.h"

namespace mulberry
{

    VKImageView::VKImageView(const VKImage *image)
        : VKImageView(image->GetHandle(), image->GetFormat(), VK_IMAGE_VIEW_TYPE_2D, ImageAspect::COLOR, image->GetMipLevel())
    {
    }
    VKImageView::VKImageView(const VKImage *image, ImageAspect aspect)
        : VKImageView(image->GetHandle(), image->GetFormat(), VK_IMAGE_VIEW_TYPE_2D, aspect, image->GetMipLevel())
    {
    }
    VKImageView::VKImageView(const VkImage &image, VkFormat format, VkImageViewType viewType, ImageAspect aspect, uint32_t mipLevels)
    {
        VkImageViewCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        info.pNext = nullptr;
        info.flags = 0;
        info.viewType = viewType;
        info.format = format;
        info.image = image;
        info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        info.subresourceRange.aspectMask = (VkImageAspectFlags)aspect;
        info.subresourceRange.baseArrayLayer = 0;
        info.subresourceRange.layerCount = 1;
        info.subresourceRange.baseMipLevel = 0;
        info.subresourceRange.levelCount = mipLevels;

        VK_CHECK(vkCreateImageView(RAW_VK_DEVICE_HANDLE, &info, nullptr, &mImageView));
    }

    VKImageView::~VKImageView()
    {
        vkDestroyImageView(RAW_VK_DEVICE_HANDLE, mImageView, nullptr);
    }

    const VkImageView &VKImageView::GetHandle() const
    {
        return mImageView;
    }
}