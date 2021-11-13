#include "DescriptorPool.h"
#include <iostream>
#include "Utils.h"
DescriptorPool::DescriptorPool(const VkDevice &device, uint32_t descriptorCount)
    : m_TmpVKDeviceHandle(device)
{
    VkDescriptorPoolSize poolSize = {};
    poolSize.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    poolSize.descriptorCount = descriptorCount;

    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.pNext = nullptr;
    poolInfo.flags = 0;
    poolInfo.maxSets = 1;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;

    VK_CHECK(vkCreateDescriptorPool(m_TmpVKDeviceHandle, &poolInfo, nullptr, &m_DescriptorPoolHandle));
}
DescriptorPool::~DescriptorPool()
{
    vkDestroyDescriptorPool(m_TmpVKDeviceHandle, m_DescriptorPoolHandle, nullptr);
}

const VkDescriptorPool &DescriptorPool::GetVKDescriptorPoolHandle() const
{
    return m_DescriptorPoolHandle;
}