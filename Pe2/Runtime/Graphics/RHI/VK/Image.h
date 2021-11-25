#pragma once
#include <vulkan/vulkan.h>
namespace VK
{
    struct Image
    {
        VkImage image;
        VkImageView imageView;
        VkDeviceMemory imageMemory;
        VkSampler imageSampler;
    };
}