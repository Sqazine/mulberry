#include "DescriptorSetLayout.h"
#include "Utils.h"
#include <iostream>
#include "Context.h"
namespace Pe2::VK
{
    DescriptorSetLayout::DescriptorSetLayout(const std::vector<VkDescriptorSetLayoutBinding> &setLayoutBindings)

    {
        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo;
        descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutInfo.pNext = nullptr;
        descriptorSetLayoutInfo.flags = 0;
        descriptorSetLayoutInfo.bindingCount = setLayoutBindings.size();
        descriptorSetLayoutInfo.pBindings = setLayoutBindings.data();

        VK_CHECK(vkCreateDescriptorSetLayout(Context::GetDevice()->GetLogicalDeviceHandle(), &descriptorSetLayoutInfo, nullptr, &m_DescriptorSetLayoutHandle));
    }
    DescriptorSetLayout::~DescriptorSetLayout()
    {
        vkDestroyDescriptorSetLayout(Context::GetDevice()->GetLogicalDeviceHandle(), m_DescriptorSetLayoutHandle, nullptr);
    }

    const VkDescriptorSetLayout &DescriptorSetLayout::GetVKDescriptorSetLayoutHandle() const
    {
        return m_DescriptorSetLayoutHandle;
    }
}