#include "PipelineLayout.h"
#include <iostream>
#include "Utils.h"
PipelineLayout::PipelineLayout(const VkDevice &device, const std::vector<VkDescriptorSetLayout> &descriptorSetLayouts, const std::vector<VkPushConstantRange> &pushConstantRange)
    : m_TmpVKDeviceHandle(device)
{
    VkPipelineLayoutCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;
    info.setLayoutCount = descriptorSetLayouts.size();
    info.pSetLayouts = descriptorSetLayouts.data();
    info.pushConstantRangeCount = pushConstantRange.size();
    info.pPushConstantRanges = pushConstantRange.data();

    VK_CHECK(vkCreatePipelineLayout(m_TmpVKDeviceHandle, &info, nullptr, &m_PipelineLayoutHandle));
}
PipelineLayout::~PipelineLayout()
{
    vkDestroyPipelineLayout(m_TmpVKDeviceHandle, m_PipelineLayoutHandle, nullptr);
}

const VkPipelineLayout &PipelineLayout::GetVKPipelineLayoutHandle() const
{
    return m_PipelineLayoutHandle;
}