#include "ImageView.h"
#include "Device.h"
#include "Utils.h"
#include "Logger.h"
#include "Context.h"

namespace mulberry::vk
{

    ImageView::ImageView(const Image *image)
        : ImageView(image->GetHandle(), image->GetFormat(), image->GetViewType(), ASPECT_COLOR, image->GetMipLevel())
    {
    }
    ImageView::ImageView(const Image *image, VkImageAspectFlags aspectFlags)
        : ImageView(image->GetHandle(), image->GetFormat(), image->GetViewType(), aspectFlags, image->GetMipLevel())
    {
    }
    ImageView::ImageView(const VkImage &image, VkFormat format, VkImageViewType viewType, VkImageAspectFlags aspectFlags, uint32_t mipLevels)
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
        info.subresourceRange.aspectMask = aspectFlags;
        info.subresourceRange.baseArrayLayer = 0;
        info.subresourceRange.layerCount = 1;
        info.subresourceRange.baseMipLevel = 0;
        info.subresourceRange.levelCount = mipLevels;

        VK_CHECK(vkCreateImageView(Context::GetInstance().GetDevice()->GetHandle(), &info, nullptr, &mImageView));
    }

    ImageView::~ImageView()
    {
        vkDestroyImageView(Context::GetInstance().GetDevice()->GetHandle(), mImageView, nullptr);
    }

    const VkImageView &ImageView::GetHandle() const
    {
        return mImageView;
    }
}