#pragma once
#include <vulkan/vulkan.h>
#include <vector>
class DescriptorSetLayout
{
public:
    DescriptorSetLayout(const VkDevice &device,const std::vector<VkDescriptorSetLayoutBinding>& setLayoutBindings);
    ~DescriptorSetLayout();

    const VkDescriptorSetLayout &GetVKDescriptorSetLayoutHandle() const;

private:
    VkDescriptorSetLayout m_DescriptorSetLayoutHandle;

    const VkDevice &m_TmpVKDeviceHandle;
};