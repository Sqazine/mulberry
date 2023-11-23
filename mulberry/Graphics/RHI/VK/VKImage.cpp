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
		VkImageTiling tiling,
		VkImageUsageFlags usage,
		VkMemoryPropertyFlags properties)
		: mFormat(format), mIsSwapChainImage(false)
	{
		mImageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		mImageInfo.pNext = nullptr;
		mImageInfo.flags = 0;
		mImageInfo.imageType = VK_IMAGE_TYPE_2D;
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

		VK_CHECK(vkCreateImage(RAW_VK_DEVICE_HANDLE, &mImageInfo, nullptr, &mImage))

		VkMemoryRequirements memRequirments;

		vkGetImageMemoryRequirements(RAW_VK_DEVICE_HANDLE, mImage, &memRequirments);

		VkMemoryAllocateInfo allocInfo;
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.pNext = nullptr;
		allocInfo.memoryTypeIndex = VK_CONTEXT->GetDevice()->FindMemoryType(memRequirments.memoryTypeBits, properties);
		allocInfo.allocationSize = memRequirments.size;

		VK_CHECK(vkAllocateMemory(RAW_VK_DEVICE_HANDLE, &allocInfo, nullptr, &mImageMemory))

		vkBindImageMemory(RAW_VK_DEVICE_HANDLE, mImage, mImageMemory, 0);

		CreateView();
	}

	VKImage::VKImage(VkImage rawImage, VkFormat format)
		: mImage(rawImage), mFormat(format), mImageLayout(VK_IMAGE_LAYOUT_UNDEFINED), mIsSwapChainImage(true)
	{
		CreateView();
	}

	VKImage::~VKImage()
	{
		vkDestroyImageView(RAW_VK_DEVICE_HANDLE, mImageView, nullptr);
		if (!mIsSwapChainImage)
		{
			vkFreeMemory(RAW_VK_DEVICE_HANDLE, mImageMemory, nullptr);
			vkDestroyImage(RAW_VK_DEVICE_HANDLE, mImage, nullptr);
		}
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

	const VkImageView &VKImage::GetView() const
	{
		return mImageView;
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

	void VKImage::CopyToBuffer(const ImageAspect &aspect, VKBuffer *buffer)
	{
		App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetGraphicsCommandPool()->SubmitOnce([&](VKCommandBuffer *cmd)
																												   {
				auto oldLayout = GetImageLayout();
				cmd->TransitionImageNewLayout(this, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

				VkBufferImageCopy copyRegion{};
				copyRegion.bufferOffset = 0;
				copyRegion.bufferRowLength = 0;
				copyRegion.bufferImageHeight = 0;
				copyRegion.imageExtent = { mImageInfo.extent.width, mImageInfo.extent.height, 1 };
				copyRegion.imageOffset = { 0, 0, 0 };
				copyRegion.imageSubresource = { (VkImageAspectFlags)aspect, 0, 0, 1 };

				vkCmdCopyImageToBuffer(cmd->GetHandle(), mImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer->GetHandle(), 1, &copyRegion);

				cmd->TransitionImageNewLayout(this, oldLayout); });
	}

	void *VKImage::MapBuffer(VKBuffer *buffer)
	{
		void *data = nullptr;
		vkMapMemory(RAW_VK_DEVICE_HANDLE, buffer->GetMemory(), 0, VK_WHOLE_SIZE, 0, (void **)&data);
		return data;
	}

	void VKImage::CreateView()
	{
		VkImageViewCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = 0;
		info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		info.format = mFormat;
		info.image = mImage;
		info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		info.subresourceRange.aspectMask = (VkImageAspectFlags)ImageAspect::COLOR;
		info.subresourceRange.baseArrayLayer = 0;
		info.subresourceRange.layerCount = 1;
		info.subresourceRange.baseMipLevel = 0;
		info.subresourceRange.levelCount = 1;

		VK_CHECK(vkCreateImageView(RAW_VK_DEVICE_HANDLE, &info, nullptr, &mImageView));
	}
}