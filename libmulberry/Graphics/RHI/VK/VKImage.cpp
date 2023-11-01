#include "VKImage.h"
#include "Logger.h"
#include "VKUtils.h"
#include "VKContext.h"
#include "VKCommand.h"
#include "App.h"
namespace mulberry
{
    VKImage::VKImage(
        uint32_t width,
        uint32_t height,
        VkFormat format,
        VkImageType type,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        VkMemoryPropertyFlags properties)
        : mFormat(format),mDevice(App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice())
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

        VK_CHECK(vkCreateImage(mDevice->GetHandle(), &mImageInfo, nullptr, &mImage))

        VkMemoryRequirements memRequirments;

        vkGetImageMemoryRequirements(mDevice->GetHandle(), mImage, &memRequirments);

        VkMemoryAllocateInfo allocInfo;
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.pNext = nullptr;
        allocInfo.memoryTypeIndex = mDevice->FindMemoryType(memRequirments.memoryTypeBits, properties);
        allocInfo.allocationSize = memRequirments.size;

        VK_CHECK(vkAllocateMemory(mDevice->GetHandle(), &allocInfo, nullptr, &mImageMemory))

        vkBindImageMemory(mDevice->GetHandle(), mImage, mImageMemory, 0);
    }

    VKImage::~VKImage()
    {
        vkFreeMemory(mDevice->GetHandle(), mImageMemory, nullptr);
        vkDestroyImage(mDevice->GetHandle(), mImage, nullptr);
    }

    const VkImage &VKImage::GetHandle() const
    {
        return mImage;
    }
    const VkDeviceMemory &VKImage::GetMemory() const
    {
        return mImageMemory;
    }

    const VkFormat &VKImage::GetFormat() const
    {
        return mFormat;
    }

    uint32_t VKImage::GetMipLevel() const
    {
        return mImageInfo.mipLevels;
    }

    const VkImageLayout &VKImage::GetImageLayout() const
    {
        return mImageLayout;
    }

    void VKImage::TransitionToNewLayout(VkImageLayout newLayout)
    {
        App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetGraphicsCommandPool()->SubmitOnce([&](VKCommandBuffer *commandBuffer)
                                                                                   { commandBuffer->TransitionImageNewLayout(this, newLayout); });

        mImageLayout = newLayout;
    }
}