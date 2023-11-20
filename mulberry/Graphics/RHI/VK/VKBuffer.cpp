#include "Logger.h"
#include "VKBuffer.h"
#include "VKUtils.h"
#include "VKDevice.h"
#include "VKCommand.h"
#include "VKContext.h"
#include "VKAdapter.h"
#include "VKDevice.h"
#include "App.h"

namespace mulberry
{
	VKBuffer::VKBuffer(VkDeviceSize size,
					   VkBufferUsageFlags usage,
					   VkMemoryPropertyFlags properties)
	{
		VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		if (!App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetPhysicalDeviceSpec().queueFamilyIndices.IsSameFamilyIndex())
			sharingMode = VK_SHARING_MODE_CONCURRENT;

		VkBufferCreateInfo bufferInfo;
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.pNext = nullptr;
		bufferInfo.flags = 0;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = sharingMode;

		VK_CHECK(vkCreateBuffer(RAW_VK_DEVICE_HANDLE, &bufferInfo, nullptr, &mBuffer));

		VkMemoryRequirements memRequirements;
		memRequirements = GetMemoryRequirements();

		mSize = memRequirements.size;

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->FindMemoryType(memRequirements.memoryTypeBits, properties);

		VK_CHECK(vkAllocateMemory(RAW_VK_DEVICE_HANDLE, &allocInfo, nullptr, &mBufferMemory));

		vkBindBufferMemory(RAW_VK_DEVICE_HANDLE, mBuffer, mBufferMemory, 0);
	}
	VKBuffer::~VKBuffer()
	{
		vkFreeMemory(RAW_VK_DEVICE_HANDLE, mBufferMemory, nullptr);
		vkDestroyBuffer(RAW_VK_DEVICE_HANDLE, mBuffer, nullptr);
	}

	VkMemoryRequirements VKBuffer::GetMemoryRequirements() const
	{
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(RAW_VK_DEVICE_HANDLE, mBuffer, &memRequirements);
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

	VKCpuBuffer::VKCpuBuffer(VkDeviceSize size, VkBufferUsageFlags usage)
		: VKBuffer(size, usage, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	{
	}

	void VKCpuBuffer::Fill(size_t size, const void *data)
	{
		void *mappedMemory = nullptr;
		vkMapMemory(RAW_VK_DEVICE_HANDLE, mBufferMemory, 0, mSize, 0, &mappedMemory);
		std::memset(mappedMemory, 0, size);
		std::memcpy(mappedMemory, data, size);
		vkUnmapMemory(RAW_VK_DEVICE_HANDLE, mBufferMemory);
	}

	void VKCpuBuffer::CopyFrom(VKCommandBuffer *commandBuffer, VkBufferCopy bufferCopy, const VKCpuBuffer &buffer)
	{
		vkCmdCopyBuffer(commandBuffer->GetHandle(), buffer.mBuffer, mBuffer, 1, &bufferCopy);
	}

	VKGpuBuffer::VKGpuBuffer(VkDeviceSize size, VkBufferUsageFlags usage)
		: VKBuffer(size, usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	{
	}

	VKGpuBuffer::VKGpuBuffer(const VKCpuBuffer &srcBuffer, VkBufferUsageFlags usage)
		: VKBuffer(srcBuffer.GetSize(), usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	{
	}

	void VKGpuBuffer::CopyFrom(class VKCommandBuffer *commandBuffer, VkBufferCopy bufferCopy, const VKCpuBuffer &buffer)
	{
	}

	void VKGpuBuffer::CopyFromStagingBuffer(VkDeviceSize bufferSize, VKCpuBuffer &stagingBuffer)
    {
       App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice()->GetGraphicsCommandPool()->SubmitOnce([bufferSize, &stagingBuffer, this](VKCommandBuffer *cmd)
                                                                                   {
                                                                                       VkBufferCopy copyRegion{};
                                                                                       copyRegion.srcOffset = 0;
                                                                                       copyRegion.dstOffset = 0;
                                                                                       copyRegion.size = bufferSize;

                                                                                       this->CopyFrom(cmd, copyRegion, stagingBuffer);
                                                                                   });
    }
}