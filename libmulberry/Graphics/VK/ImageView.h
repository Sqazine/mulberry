#pragma once
#include <vulkan/vulkan.h>
#include "Image.h"
namespace mulberry::vk
{
    class ImageView
    {
    public:
        ImageView(const Image *image);
        ImageView(const Image *image, VkImageAspectFlags aspectFlags);
        ImageView(const VkImage &image, VkFormat format, VkImageViewType viewType, VkImageAspectFlags aspectFlags, uint32_t mipLevels = 1);
        ~ImageView();

        const VkImageView &GetHandle() const;

    private:
        VkImageView mImageView;
    };
}