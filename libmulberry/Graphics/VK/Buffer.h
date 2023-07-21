#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "Utils.h"
#include "Vec2.h"

namespace mulberry::vk
{
	class Buffer
	{
	public:
		Buffer(VkDeviceSize size,
			   VkBufferUsageFlags usage,
			   VkMemoryPropertyFlags properties);

		Buffer(void *srcData,
			   VkDeviceSize size,
			   VkBufferUsageFlags usage,
			   VkMemoryPropertyFlags properties);

		~Buffer();

		const VkBuffer &GetHandle() const;
		const VkDeviceMemory &GetMemory() const;
		const VkDeviceSize &GetSize() const;
		
	protected:
		VkMemoryRequirements GetMemoryRequirements() const;

		VkBuffer mBuffer;
		VkDeviceMemory mBufferMemory;
		VkDeviceSize mSize;
	};

	class CpuBuffer : public Buffer
	{
	public:
		CpuBuffer(VkDeviceSize size,
				  VkBufferUsageFlags usage);
		template <typename T>
		CpuBuffer(const std::vector<T> &srcData,
				  VkBufferUsageFlags usage);

		void Fill(size_t size, const void *data);
		void CopyFrom(class CommandBuffer *commandBuffer, VkBufferCopy bufferCopy, const CpuBuffer &buffer);
	};

	class GpuBuffer : public Buffer
	{
	public:
		GpuBuffer(VkDeviceSize size,
				  VkBufferUsageFlags usage);

		GpuBuffer(const CpuBuffer &srcBuffer,
				  VkBufferUsageFlags usage);
	};
}