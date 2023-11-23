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
			VkImageTiling tiling,
			VkImageUsageFlags usage,
			VkMemoryPropertyFlags properties);

		VKImage(VkImage rawImage, VkFormat format);

		virtual ~VKImage();

		const VkImage &GetHandle() const;
		const VkDeviceMemory &GetMemory() const;
		const VkFormat &GetFormat() const;
		const VkImageView& GetView() const;
		uint32_t GetMipLevel() const;

		const VkImageLayout &GetImageLayout() const;

		void TransitionToNewLayout(VkImageLayout newLayout);

		template <typename T>
		std::vector<T> GetRawData(const ImageAspect &aspect);

	protected:
		friend class VKCommandBuffer;
		VkImageLayout mImageLayout;

		VkImageCreateInfo mImageInfo;
		VkImage mImage;
		VkImageView mImageView;
		VkFormat mFormat;
		VkDeviceMemory mImageMemory;

		bool mIsSwapChainImage;
	private:
		void CreateView();

		void CopyToBuffer(const ImageAspect &aspect, VKBuffer *buffer);
		void *MapBuffer(VKBuffer *buffer);
	};

	template <typename T>
	std::vector<T> VKImage::GetRawData(const ImageAspect &aspect)
	{
		auto srcImg = this;

		auto stagingBuffer = std::make_unique<VKBuffer>(mImageInfo.extent.width * mImageInfo.extent.height * sizeof(T), VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		CopyToBuffer(aspect, stagingBuffer.get());

		std::vector<T> result(mImageInfo.extent.width * mImageInfo.extent.height);

		T *data = MapBuffer(stagingBuffer.get());

		for (int32_t i = 0; i < mImageInfo.extent.width * mImageInfo.extent.height; ++i)
			result[i] = data[i];

		return result;
	}
}
