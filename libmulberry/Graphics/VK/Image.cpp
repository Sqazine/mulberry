#include "Image.h"
#include "Logger.h"
#include "Utils.h"
#include "Context.h"
#include "Command.h"

namespace mulberry::vk
{

    Image::Image(
        uint32_t width,
        uint32_t height,
        VkFormat format,
        VkImageType type,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        VkMemoryPropertyFlags properties)
        : mFormat(format)
    {
        mImageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        mImageInfo.pNext = nullptr;
        mImageInfo.flags = 0;
        mImageInfo.imageType = type;
        mImageInfo.extent.width = width;
        mImageInfo.extent.height = height;
        mImageInfo.extent.depth = 1;
        mImageInfo.mipLevels = 1;
        mImageInfo.arrayLayers = 1;
        mImageInfo.format = mFormat;
        mImageInfo.tiling = tiling;
        mImageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        mImageInfo.usage = usage;
        mImageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        mImageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        mImageInfo.queueFamilyIndexCount = 0;
        mImageInfo.pQueueFamilyIndices = nullptr;

        mImageLayout = mImageInfo.initialLayout;

        VK_CHECK(vkCreateImage(Context::GetInstance().GetDevice()->GetHandle(), &mImageInfo, nullptr, &mImage))

        VkMemoryRequirements memRequirments;

        vkGetImageMemoryRequirements(Context::GetInstance().GetDevice()->GetHandle(), mImage, &memRequirments);

        VkMemoryAllocateInfo allocInfo;
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.pNext = nullptr;
        allocInfo.memoryTypeIndex = Context::GetInstance().GetDevice()->FindMemoryType(memRequirments.memoryTypeBits, properties);
        allocInfo.allocationSize = memRequirments.size;

        VK_CHECK(vkAllocateMemory(Context::GetInstance().GetDevice()->GetHandle(), &allocInfo, nullptr, &mImageMemory))

        vkBindImageMemory(Context::GetInstance().GetDevice()->GetHandle(), mImage, mImageMemory, 0);
    }

    Image::~Image()
    {
        vkFreeMemory(Context::GetInstance().GetDevice()->GetHandle(), mImageMemory, nullptr);
        vkDestroyImage(Context::GetInstance().GetDevice()->GetHandle(), mImage, nullptr);
    }

    const VkImage &Image::GetHandle() const
    {
        return mImage;
    }
    const VkDeviceMemory &Image::GetMemory() const
    {
        return mImageMemory;
    }

    const VkFormat &Image::GetFormat() const
    {
        return mFormat;
    }

    uint32_t Image::GetMipLevel() const
    {
        return mImageInfo.mipLevels;
    }

    const VkImageLayout &Image::GetImageLayout() const
    {
        return mImageLayout;
    }

    void Image::TransitionToNewLayout(VkImageLayout newLayout)
    {
        Context::GetInstance().GetDevice()->GetGraphicsCommandPool()->SubmitOnce([&](CommandBuffer *commandBuffer)
                                                                   { commandBuffer->TransitionImageNewLayout(this, newLayout); });

        mImageLayout = newLayout;
    }
}