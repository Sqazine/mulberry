#pragma once
#include <vulkan/vulkan.h>
#include <vector>
namespace Pe2::VK
{
    class PipelineLayout
    {
    public:
        PipelineLayout( const std::vector<VkDescriptorSetLayout> &descriptorSetLayouts = {}, const std::vector<VkPushConstantRange> &pushConstantRange = {});
        ~PipelineLayout();

        const VkPipelineLayout &GetVKPipelineLayoutHandle() const;

    private:
        VkPipelineLayout m_PipelineLayoutHandle;
        
    };
}