#pragma once
#include <vulkan/vulkan.h>
#include "VKDevice.h"
#include "VKCommand.h"

namespace mulberry
{
	enum ImageAspect
	{
		COLOR = VK_IMAGE_ASPECT_COLOR_BIT,
		DEPTH = VK_IMAGE_ASPECT_DEPTH_BIT,
		STENCIL = VK_IMAGE_ASPECT_STENCIL_BIT,
	};

	class VKImage
	{
	public:
		VKImage(
			uint32_t width,
			uint32_t height,
			VkFormat format,
			VkImageType type,
			VkImageTiling tiling,
			VkImageUsageFlags usage,
			VkMemoryPropertyFlags properties);

		virtual ~VKImage();

		const VkImage& GetHandle() const;
		const VkDeviceMemory& GetMemory() const;
		const VkFormat& GetFormat() const;
		uint32_t GetMipLevel() const;

		const VkImageLayout& GetImageLayout() const;

		virtual VkImageViewType GetViewType() const = 0;

		void TransitionToNewLayout(VkImageLayout newLayout);

		template <typename T>
		std::vector<T> GetRawData(const ImageAspect& aspect);

	protected:
		VkImageCreateInfo mImageInfo;
		VkImage mImage;
		VkFormat mFormat;
		VkDeviceMemory mImageMemory;

		friend class VKCommandBuffer;

		VkImageLayout mImageLayout;
	};

	template <typename T>
	std::vector<T> VKImage::GetRawData(const ImageAspect& aspect)
	{
		auto srcImg = this;

		auto stagingBuffer = std::make_unique<VKBuffer>(mImageInfo.extent.width * mImageInfo.extent.height * sizeof(T), VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		VKContext::GetDevice()->GetGraphicsCommandPool()->SubmitOnce([&](VKCommandBuffer* cmd)
			{
				auto oldLayout = srcImg->GetImageLayout();
				cmd->TransitionImageNewLayout(srcImg, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

				VkBufferImageCopy copyRegion{};
				copyRegion.bufferOffset = 0;
				copyRegion.bufferRowLength = 0;
				copyRegion.bufferImageHeight = 0;
				copyRegion.imageExtent = { mImageInfo.extent.width, mImageInfo.extent.height, 1 };
				copyRegion.imageOffset = { 0, 0, 0 };
				copyRegion.imageSubresource = { (VkImageAspectFlags)aspect, 0, 0, 1 };

				vkCmdCopyImageToBuffer(cmd->GetHandle(), srcImg->GetHandle(), VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, stagingBuffer->GetBuffer(), 1, &copyRegion);

				cmd->TransitionImageNewLayout(srcImg, oldLayout);
			});

		std::vector<T> result(mImageInfo.extent.width * mImageInfo.extent.height);

		T* data = nullptr;
		vkMapMemory(VKContext::GetInstance().GetDevice(), stagingBuffer->GetMemory(), 0, VK_WHOLE_SIZE, 0, (void**)&data);

		for (int32_t i = 0; i < mImageInfo.extent.width * mImageInfo.extent.height; ++i)
			result[i] = data[i];

		return result;
	}
}
