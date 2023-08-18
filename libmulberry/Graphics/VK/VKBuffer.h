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

	class VKGpuBuffer : public VKBuffer
	{
	public:
		VKGpuBuffer(VkDeviceSize size,
				  VkBufferUsageFlags usage);

		VKGpuBuffer(const VKCpuBuffer &srcBuffer,
				  VkBufferUsageFlags usage);
	};
}