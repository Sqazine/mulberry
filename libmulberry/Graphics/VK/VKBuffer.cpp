#include "Logger.h"
#include "VKBuffer.h"
#include "VKUtils.h"
#include "VKDevice.h"
#include "VKCommand.h"
#include "VKContext.h"
#include "VKAdapter.h"
#include "VKDevice.h"

namespace mulberry
{
	VKBuffer::VKBuffer(VkDeviceSize size,
				   VkBufferUsageFlags usage,
				   VkMemoryPropertyFlags properties)
	{
		VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		if (!VKContext::GetInstance().GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.IsSameFamilyIndex())
			sharingMode = VK_SHARING_MODE_CONCURRENT;

		VkBufferCreateInfo bufferInfo;
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.pNext = nullptr;
		bufferInfo.flags = 0;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = sharingMode;

		VK_CHECK(vkCreateBuffer(VKContext::GetInstance().GetDevice()->GetHandle(), &bufferInfo, nullptr, &mBuffer));

		VkMemoryRequirements memRequirements;
		memRequirements = GetMemoryRequirements();

		mSize = memRequirements.size;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = VKContext::GetInstance().GetDevice()->FindMemoryType(memRequirements.memoryTypeBits, properties);

		VK_CHECK(vkAllocateMemory(VKContext::GetInstance().GetDevice()->GetHandle(), &allocInfo, nullptr, &mBufferMemory));

		vkBindBufferMemory(VKContext::GetInstance().GetDevice()->GetHandle(), mBuffer, mBufferMemory, 0);
	}
	VKBuffer::~VKBuffer()
	{
		vkFreeMemory(VKContext::GetInstance().GetDevice()->GetHandle(), mBufferMemory, nullptr);
		vkDestroyBuffer(VKContext::GetInstance().GetDevice()->GetHandle(), mBuffer, nullptr);
	}

	VkMemoryRequirements VKBuffer::GetMemoryRequirements() const
	{
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(VKContext::GetInstance().GetDevice()->GetHandle(), mBuffer, &memRequirements);
		return memRequirements;
	}

	const VkBuffer &VKBuffer::GetHandle() const
	{
		return mBuffer;
	}
	const VkDeviceMemory &VKBuffer::GetMemory() const
	{
		return mBufferMemory;
	}

	const VkDeviceSize &VKBuffer::GetSize() const
	{
		return mSize;
	}

	void VKCpuBuffer::Fill(size_t size, const void *data)
	{
		void *mappedMemory = nullptr;
		vkMapMemory(VKContext::GetInstance().GetDevice()->GetHandle(), mBufferMemory, 0, mSize, 0, &mappedMemory);
		std::memset(mappedMemory, 0, size);
		std::memcpy(mappedMemory, data, size);
		vkUnmapMemory(VKContext::GetInstance().GetDevice()->GetHandle(), mBufferMemory);
	}

	void VKCpuBuffer::CopyFrom(VKCommandBuffer *commandBuffer, VkBufferCopy bufferCopy, const VKCpuBuffer &buffer)
	{
		vkCmdCopyBuffer(commandBuffer->GetHandle(), buffer.mBuffer, mBuffer, 1, &bufferCopy);
	}
}