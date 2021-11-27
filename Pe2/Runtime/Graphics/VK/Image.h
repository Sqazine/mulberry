#pragma once
#include <vulkan/vulkan.h>
namespace Pe2::VK
{
    struct Image
    {
        VkImage image;
        VkImageView imageView;
        VkDeviceMemory imageMemory;
        VkSampler imageSampler;
    };
}