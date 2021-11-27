#include "Buffer.h"
#include "Utils.h"
#include "Device.h"
#include <iostream>
#include "Context.h"
namespace Pe2::VK
{
    Buffer::Buffer(
                   VkDeviceSize size,
                   VkBufferUsageFlags usage,
                   VkSharingMode sharingMode,
                   VkMemoryPropertyFlags properties)
        : Buffer(size, usage, sharingMode, 0, properties)
    {
    }

    Buffer::Buffer(
                   VkDeviceSize size,
                   VkBufferUsageFlags usage,
                   VkSharingMode sharingMode,
                   VkMemoryAllocateFlags allocateFlags,
                   VkMemoryPropertyFlags properties)
    {
        VkBufferCreateInfo bufferInfo;
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.pNext = nullptr;
        bufferInfo.flags = 0;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = sharingMode;

        VK_CHECK(vkCreateBuffer(Context::GetDevice()->GetLogicalDeviceHandle(), &bufferInfo, nullptr, &m_BufferHandle));

        VkMemoryRequirements memRequirements;
        memRequirements = GetMemoryRequirements();

        VkMemoryAllocateFlagsInfo flagsInfo{};
        flagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
        flagsInfo.pNext = nullptr;
        flagsInfo.flags = allocateFlags;
        flagsInfo.deviceMask = -1;

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = Context::GetDevice()->FindMemoryType(memRequirements.memoryTypeBits, properties);
        allocInfo.pNext = &flagsInfo;

        VK_CHECK(vkAllocateMemory(Context::GetDevice()->GetLogicalDeviceHandle(), &allocInfo, nullptr, &m_BufferMemoryHandle));

        vkBindBufferMemory(Context::GetDevice()->GetLogicalDeviceHandle(), m_BufferHandle, m_BufferMemoryHandle, 0);
    }
    Buffer::~Buffer()
    {
        vkFreeMemory(Context::GetDevice()->GetLogicalDeviceHandle(), m_BufferMemoryHandle, nullptr);
        vkDestroyBuffer(Context::GetDevice()->GetLogicalDeviceHandle(), m_BufferHandle, nullptr);
    }

    VkMemoryRequirements Buffer::GetMemoryRequirements() const
    {
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(Context::GetDevice()->GetLogicalDeviceHandle(), m_BufferHandle, &memRequirements);
        return memRequirements;
    }

    const VkBuffer &Buffer::GetVKBufferHandle() const
    {
        return m_BufferHandle;
    }
    const VkDeviceMemory &Buffer::GetVKBufferMemory() const
    {
        return m_BufferMemoryHandle;
    }
}