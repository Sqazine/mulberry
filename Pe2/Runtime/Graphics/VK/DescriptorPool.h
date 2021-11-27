#pragma once
#include <vulkan/vulkan.h>
namespace Pe2::VK
{
    class DescriptorPool
    {
    public:
        DescriptorPool(uint32_t descriptorCount);
        ~DescriptorPool();

        const VkDescriptorPool &GetVKDescriptorPoolHandle() const;

    private:
        VkDescriptorPool m_DescriptorPoolHandle;
        
    };
}