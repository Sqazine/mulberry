#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VKUtils.h"
#include "Vec2.h"

namespace mulberry
{
	class VKBuffer
	{
	public:
		VKBuffer(VkDeviceSize size,
				 VkBufferUsageFlags usage,
				 VkMemoryPropertyFlags properties);

		VKBuffer(void *srcData,
				 VkDeviceSize size,
				 VkBufferUsageFlags usage,
				 VkMemoryPropertyFlags properties);

		~VKBuffer();

		const VkBuffer &GetHandle() const;
		const VkDeviceMemory &GetMemory() const;
		const VkDeviceSize &GetSize() const;

	protected:
		VkMemoryRequirements GetMemoryRequirements() const;

		VkBuffer mBuffer;
		VkDeviceMemory mBufferMemory;
		VkDeviceSize mSize;
	};

	class VKCpuBuffer : public VKBuffer
	{
	public:
		VKCpuBuffer(VkDeviceSize size,
					VkBufferUsageFlags usage);

		template <typename T>
		VKCpuBuffer(const std::vector<T> &srcData,
					VkBufferUsageFlags usage);

		void Fill(size_t size, const void *data);
		void CopyFrom(class VKCommandBuffer *commandBuffer, VkBufferCopy bufferCopy, const VKCpuBuffer &buffer);
	};

	template <typename T>
	VKCpuBuffer::VKCpuBuffer(const std::vector<T> &srcData, VkBufferUsageFlags usage)
		: VKBuffer(srcData.data(), sizeof(T) * srcData.size(), usage, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	{
	}

	class VKGpuBuffer : public VKBuffer
	{
	public:
		VKGpuBuffer(VkDeviceSize size,
					VkBufferUsageFlags usage);

		VKGpuBuffer(const VKCpuBuffer &srcBuffer,
					VkBufferUsageFlags usage);

		void CopyFrom(class VKCommandBuffer *commandBuffer, VkBufferCopy bufferCopy, const VKCpuBuffer &buffer);
	
		 void CopyFromStagingBuffer(VkDeviceSize bufferSize, VKCpuBuffer &stagingBuffer);
	};
}