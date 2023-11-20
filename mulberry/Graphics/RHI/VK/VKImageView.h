#pragma once
#include <vulkan/vulkan.h>
#include "VKImage.h"
namespace mulberry
{
    class VKImageView
    {
    public:
        VKImageView(const VKImage *image);
        VKImageView(const VKImage *image, ImageAspect aspect);
        VKImageView(const VkImage &image, VkFormat format, VkImageViewType viewType, ImageAspect aspect, uint32_t mipLevels = 1);
        ~VKImageView();

        const VkImageView &GetHandle() const;

    private:
        VkImageView mImageView;
    };
}