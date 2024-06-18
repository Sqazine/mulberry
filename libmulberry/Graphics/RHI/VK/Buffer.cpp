#include "Logger.h"
#include "Buffer.h"
#include "Utils.h"
#include "Device.h"
#include "Command.h"
#include "GraphicsContext.h"
#include "Adapter.h"
#include "Device.h"

namespace mulberry::vk
{
	Buffer::Buffer(uint64_t size,
				   BufferUsage usage,
				   MemoryProperty properties)
		: mSize(size)
	{
		VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		if (!mDevice.GetPhysicalDeviceSpec().queueFamilyIndices.IsSameFamilyIndex())
			sharingMode = VK_SHARING_MODE_CONCURRENT;

		VkBufferCreateInfo bufferInfo;
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.pNext = nullptr;
		bufferInfo.flags = 0;
		bufferInfo.size = mSize;
		bufferInfo.usage = BUFFER_USAGE_CAST(usage);
		bufferInfo.sharingMode = sharingMode;

		VK_CHECK(vkCreateBuffer(mDevice.GetHandle(), &bufferInfo, nullptr, &mBuffer));

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(mDevice.GetHandle(), mBuffer, &memRequirements);
		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.memoryTypeIndex = mDevice.FindMemoryType(memRequirements.memoryTypeBits, properties);
		allocInfo.allocationSize = memRequirements.size;
		VK_CHECK(vkAllocateMemory(mDevice.GetHandle(), &allocInfo, nullptr, &mBufferMemory));
		vkBindBufferMemory(mDevice.GetHandle(), mBuffer, mBufferMemory, 0);
	}

	Buffer::~Buffer()
	{
		vkFreeMemory(mDevice.GetHandle(), mBufferMemory, nullptr);
		vkDestroyBuffer(mDevice.GetHandle(), mBuffer, nullptr);
	}

	const VkBuffer &Buffer::GetHandle() const
	{
		return mBuffer;
	}
	const VkDeviceMemory &Buffer::GetMemory() const
	{
		return mBufferMemory;
	}

	const uint64_t &Buffer::GetSize() const
	{
		return mSize;
	}

	CpuBuffer::CpuBuffer(uint64_t size, BufferUsage usage)
		: Buffer(size, usage, MemoryProperty::HOST_VISIBLE | MemoryProperty::HOST_COHERENT)
	{
	}

	void CpuBuffer::Fill(size_t size, const void *data)
	{
		void *mappedMemory = nullptr;
		vkMapMemory(mDevice.GetHandle(), mBufferMemory, 0, mSize, 0, &mappedMemory);
		std::memset(mappedMemory, 0, size);
		std::memcpy(mappedMemory, data, size);
		vkUnmapMemory(mDevice.GetHandle(), mBufferMemory);
	}

	GpuBuffer::GpuBuffer(uint64_t size, BufferUsage usage)
		: Buffer(size, usage, MemoryProperty::DEVICE_LOCAL)
	{
	}

	GpuBuffer::GpuBuffer(const CpuBuffer &srcBuffer, BufferUsage usage)
		: Buffer(srcBuffer.GetSize(), usage, MemoryProperty::DEVICE_LOCAL)
	{
	}

	void GpuBuffer::UploadDataFrom(uint64_t bufferSize, CpuBuffer &stagingBuffer)
	{
		auto cmd = mDevice.GetTransferCommandPool()->CreatePrimaryCommandBuffer();

		cmd->ExecuteImmediately([&]()
								{
			VkBufferCopy copyRegion{};
			copyRegion.srcOffset = 0;
			copyRegion.dstOffset = 0;
			copyRegion.size = bufferSize;

			cmd->CopyBuffer(*this,stagingBuffer, copyRegion); });
	}

	IndexBuffer::IndexBuffer()
		: GpuBuffer(0, BufferUsage::TRANSFER_DST | BufferUsage::INDEX)
	{
	}

	VkIndexType IndexBuffer::GetDataType() const
	{
		return mDataType;
	}

	VkIndexType IndexBuffer::DataStr2VkIndexType(std::string_view dataStr) const
	{
		if (dataStr.compare("uint32_t") == 0 || dataStr.compare("unsigned int") == 0)
			return VK_INDEX_TYPE_UINT32;
		else if (dataStr.compare("uint8_t") == 0 || dataStr.compare("unsigned char") == 0)
			return VK_INDEX_TYPE_UINT8_EXT;
		else if (dataStr.compare("uint16_t") == 0 || dataStr.compare("unsigned short") == 0)
			return VK_INDEX_TYPE_UINT16;
		return VK_INDEX_TYPE_UINT32;
	}
}