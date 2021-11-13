#pragma once
#include <vulkan/vulkan.h>
#include <vector>
class PipelineLayout
{
public:
    PipelineLayout(const VkDevice &device, const std::vector<VkDescriptorSetLayout> &descriptorSetLayouts={}, const std::vector<VkPushConstantRange> &pushConstantRange={});
    ~PipelineLayout();

    const VkPipelineLayout& GetVKPipelineLayoutHandle() const;
private:
    VkPipelineLayout m_PipelineLayoutHandle;
    const VkDevice &m_TmpVKDeviceHandle;
};