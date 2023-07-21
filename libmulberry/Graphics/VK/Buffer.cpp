#include "Logger.h"
#include "Buffer.h"
#include "Utils.h"
#include "Device.h"
#include "Command.h"
#include "Context.h"
#include "Adapter.h"
#include "Device.h"

namespace mulberry::vk
{
	Buffer::Buffer(VkDeviceSize size,
				   VkBufferUsageFlags usage,
				   VkMemoryPropertyFlags properties)
	{
		VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		if (!Context::GetInstance().GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.IsSameFamilyIndex())
			sharingMode = VK_SHARING_MODE_CONCURRENT;

		VkBufferCreateInfo bufferInfo;
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.pNext = nullptr;
		bufferInfo.flags = 0;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = sharingMode;

		VK_CHECK(vkCreateBuffer(Context::GetInstance().GetDevice()->GetHandle(), &bufferInfo, nullptr, &mBuffer));

		VkMemoryRequirements memRequirements;
		memRequirements = GetMemoryRequirements();

		mSize = memRequirements.size;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = Context::GetInstance().GetDevice()->FindMemoryType(memRequirements.memoryTypeBits, properties);

		VK_CHECK(vkAllocateMemory(Context::GetInstance().GetDevice()->GetHandle(), &allocInfo, nullptr, &mBufferMemory));

		vkBindBufferMemory(Context::GetInstance().GetDevice()->GetHandle(), mBuffer, mBufferMemory, 0);
	}
	Buffer::~Buffer()
	{
		vkFreeMemory(Context::GetInstance().GetDevice()->GetHandle(), mBufferMemory, nullptr);
		vkDestroyBuffer(Context::GetInstance().GetDevice()->GetHandle(), mBuffer, nullptr);
	}

	VkMemoryRequirements Buffer::GetMemoryRequirements() const
	{
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(Context::GetInstance().GetDevice()->GetHandle(), mBuffer, &memRequirements);
		return memRequirements;
	}

	const VkBuffer &Buffer::GetHandle() const
	{
		return mBuffer;
	}
	const VkDeviceMemory &Buffer::GetMemory() const
	{
		return mBufferMemory;
	}

	const VkDeviceSize &Buffer::GetSize() const
	{
		return mSize;
	}

	void CpuBuffer::Fill(size_t size, const void *data)
	{
		void *mappedMemory = nullptr;
		vkMapMemory(Context::GetInstance().GetDevice()->GetHandle(), mBufferMemory, 0, mSize, 0, &mappedMemory);
		std::memset(mappedMemory, 0, size);
		std::memcpy(mappedMemory, data, size);
		vkUnmapMemory(Context::GetInstance().GetDevice()->GetHandle(), mBufferMemory);
	}

	void CpuBuffer::CopyFrom(class CommandBuffer *commandBuffer, VkBufferCopy bufferCopy, const CpuBuffer &buffer)
	{
		vkCmdCopyBuffer(commandBuffer->GetHandle(), buffer.mBuffer, mBuffer, 1, &bufferCopy);
	}
}