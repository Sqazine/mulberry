#pragma once
#include <vulkan/vulkan.h>
#include "Device.h"
#include "Buffer.h"
#include "Object.h"
#include "../Enum.h"
#include "../Format.h"
namespace mulberry::vk
{
	class Image : public Object
	{
	public:
		Image(
			uint32_t width,
			uint32_t height,
			Format format,
			ImageTiling tiling,
			ImageUsage usage,
			MemoryProperty properties);

		Image(const Vec2& extent, VkImage rawImage, Format format);
		virtual ~Image();

		const VkImage &GetHandle() const;
		const VkDeviceMemory &GetMemory() const;
		const Format &GetFormat() const;
		const VkImageView &GetView() const;
		uint32_t GetMipLevel() const;

		const ImageLayout &GetImageLayout() const;

		void TransitionToNewLayout(ImageLayout newLayout);

		template <typename T>
		std::vector<T> GetRawData();

		Vec2 GetExtent() const;
	protected:
		friend class CommandBuffer;
		ImageLayout mLayout;

		VkImageCreateInfo mImageInfo;
		VkImage mHandle;
		VkImageView mView;
		Format mFormat;
		VkDeviceMemory mMemory;

		bool mIsSwapChainImage;

	private:
		void CreateView();

		void CopyToBuffer(Buffer *buffer);
		void *MapBuffer(Buffer *buffer);
	};

	template <typename T>
	std::vector<T> Image::GetRawData()
	{
		auto srcImg = this;

		auto stagingBuffer = std::make_unique<Buffer>(mImageInfo.extent.width * mImageInfo.extent.height * sizeof(T), VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		CopyToBuffer(stagingBuffer.get());

		std::vector<T> result(mImageInfo.extent.width * mImageInfo.extent.height);

		T *data = MapBuffer(stagingBuffer.get());

		for (int32_t i = 0; i < mImageInfo.extent.width * mImageInfo.extent.height; ++i)
			result[i] = data[i];

		return result;
	}

	class CpuImage : public Image
	{
	public:
		CpuImage(uint32_t width, uint32_t height, Format format, ImageTiling tiling, ImageUsage usage);
		~CpuImage() override;
	};

	class GpuImage : public Image
	{
	public:
		GpuImage(class Device& device, uint32_t width, uint32_t height, Format format, ImageTiling tiling, ImageUsage usage);
		~GpuImage() override;

		void UploadDataFrom(uint64_t bufferSize, CpuBuffer* stagingBuffer, ImageLayout oldLayout, ImageLayout newLayout);
	};
}
