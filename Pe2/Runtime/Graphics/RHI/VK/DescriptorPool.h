#pragma once
#include <vulkan/vulkan.h>
class DescriptorPool
{
public:
    DescriptorPool(const VkDevice& device,uint32_t descriptorCount);
    ~DescriptorPool();

    const VkDescriptorPool& GetVKDescriptorPoolHandle() const;
private:
    VkDescriptorPool m_DescriptorPoolHandle;
    const VkDevice &m_TmpVKDeviceHandle;
};