#include "Image.h"
#include "Logger.h"
#include "Utils.h"
#include "Context.h"
#include "CommandBuffer.h"
#include "CommandPool.h"
namespace mulberry::vk
{
	Image::Image(
		uint32_t width,
		uint32_t height,
		Format format,
		ImageTiling tiling,
		ImageUsage usage,
		MemoryProperty properties)
		: mFormat(format), mIsSwapChainImage(false)
	{
		mImageLayout = ImageLayout::UNDEFINED;

		mImageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		mImageInfo.pNext = nullptr;
		mImageInfo.flags = 0;
		mImageInfo.imageType = VK_IMAGE_TYPE_2D;
		mImageInfo.extent.width = width;
		mImageInfo.extent.height = height;
		mImageInfo.extent.depth = 1;
		mImageInfo.mipLevels = 1;
		mImageInfo.arrayLayers = 1;
		mImageInfo.format = mFormat.ToVkHandle();
		mImageInfo.tiling = IMAGE_TILING_CAST(tiling);
		mImageInfo.initialLayout = IMAGE_LAYOUT_CAST(mImageLayout);
		mImageInfo.usage = IMAGE_USAGE_CAST(usage);
		mImageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		mImageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		mImageInfo.queueFamilyIndexCount = 0;
		mImageInfo.pQueueFamilyIndices = nullptr;

		VK_CHECK(vkCreateImage(mDevice.GetHandle(), &mImageInfo, nullptr, &mImage))

		VkMemoryRequirements memRequirments;

		vkGetImageMemoryRequirements(mDevice.GetHandle(), mImage, &memRequirments);

		VkMemoryAllocateInfo allocInfo;
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.pNext = nullptr;
		allocInfo.memoryTypeIndex = mDevice.FindMemoryType(memRequirments.memoryTypeBits, properties);
		allocInfo.allocationSize = memRequirments.size;

		VK_CHECK(vkAllocateMemory(mDevice.GetHandle(), &allocInfo, nullptr, &mImageMemory))

		vkBindImageMemory(mDevice.GetHandle(), mImage, mImageMemory, 0);

		CreateView();
	}

	Image::Image(VkImage rawImage, Format format)
		: mImage(rawImage), mFormat(format), mImageLayout(ImageLayout::UNDEFINED), mIsSwapChainImage(true)
	{
		CreateView();
	}

	Image::~Image()
	{
		vkDestroyImageView(mDevice.GetHandle(), mImageView, nullptr);
		if (!mIsSwapChainImage)
		{
			vkFreeMemory(mDevice.GetHandle(), mImageMemory, nullptr);
			vkDestroyImage(mDevice.GetHandle(), mImage, nullptr);
		}
	}

	const VkImage &Image::GetHandle() const
	{
		return mImage;
	}
	const VkDeviceMemory &Image::GetMemory() const
	{
		return mImageMemory;
	}

	const Format &Image::GetFormat() const
	{
		return mFormat;
	}

	const VkImageView &Image::GetView() const
	{
		return mImageView;
	}

	uint32_t Image::GetMipLevel() const
	{
		return mImageInfo.mipLevels;
	}

	const ImageLayout &Image::GetImageLayout() const
	{
		return mImageLayout;
	}

	void Image::TransitionToNewLayout(ImageLayout newLayout)
	{
		auto cmd = mDevice.GetTransferCommandPool()->CreatePrimaryCommandBuffer();

		cmd->ExecuteImmediately([&]()
								{ cmd->TransitionImageNewLayout(this, newLayout); });

		mImageLayout = newLayout;
	}

	uint32_t Image::GetWidth() const
	{
		return mImageInfo.extent.width;
	}

	uint32_t Image::GetHeight() const
	{
		return mImageInfo.extent.height;
	}

	Vec2 Image::GetExtent() const
	{
		return Vec2(mImageInfo.extent.width, mImageInfo.extent.height);
	}

	void Image::CopyToBuffer(Buffer *buffer)
	{
		auto cmd = mDevice.GetTransferCommandPool()->CreatePrimaryCommandBuffer();
		cmd->ExecuteImmediately([&]()
								{
			auto oldLayout = GetImageLayout();
			cmd->TransitionImageNewLayout(this,ImageLayout::TRANSFER_SRC_OPTIMAL);

			VkBufferImageCopy copyRegion{};
			copyRegion.bufferOffset = 0;
			copyRegion.bufferRowLength = 0;
			copyRegion.bufferImageHeight = 0;
			copyRegion.imageExtent = { mImageInfo.extent.width, mImageInfo.extent.height, 1 };
			copyRegion.imageOffset = { 0, 0, 0 };

			ImageAspect aspect = ImageAspect::NONE;

			if (mFormat.HasDepth())
				aspect = ImageAspect::DEPTH;
			else if (mFormat.HasStencil())
				aspect = ImageAspect::STENCIL;
			else
				aspect = ImageAspect::COLOR;

			copyRegion.imageSubresource = { IMAGE_ASPECT_CAST(aspect), 0, 0, 1};

			vkCmdCopyImageToBuffer(cmd->GetHandle(), mImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer->GetHandle(), 1, &copyRegion);

			cmd->TransitionImageNewLayout(this, oldLayout); });
	}

	void *Image::MapBuffer(Buffer *buffer)
	{
		void *data = nullptr;
		vkMapMemory(mDevice.GetHandle(), buffer->GetMemory(), 0, VK_WHOLE_SIZE, 0, (void **)&data);
		return data;
	}

	void Image::CreateView()
	{
		VkImageViewCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		info.pNext = nullptr;
		info.flags = 0;
		info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		info.format = mFormat.ToVkHandle();
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

		VK_CHECK(vkCreateImageView(mDevice.GetHandle(), &info, nullptr, &mImageView));
	}
}