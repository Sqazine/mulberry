#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "Object.h"
#include "../Enum.h"
namespace mulberry::vk
{
    struct DescriptorBinding
    {
        uint32_t bindingPoint;
        uint32_t count;
        DescriptorType type;
        ShaderStage shaderStage;

        DescriptorBinding(uint32_t bindingPoint, uint32_t count, DescriptorType type, ShaderStage shaderStage)
            : bindingPoint(bindingPoint), count(count), type(type), shaderStage(shaderStage)
        {
        }

        VkDescriptorSetLayoutBinding ToVkDescriptorBinding() const
        {
            VkDescriptorSetLayoutBinding tmp{};
            tmp.binding = bindingPoint;
            tmp.descriptorCount = count;
            tmp.descriptorType = DESCRIPTOR_TYPE_CAST(type);
            tmp.stageFlags = SHADER_STAGE_CAST(shaderStage);
            tmp.pImmutableSamplers = VK_NULL_HANDLE;
            return tmp;
        }
    };

    class DescriptorSetLayout : public Object
    {
    public:
        DescriptorSetLayout();
        DescriptorSetLayout(const std::vector<DescriptorBinding> &setLayoutBindings);
        virtual ~DescriptorSetLayout();

        DescriptorSetLayout &AddLayoutBinding(const DescriptorBinding &binding);
        DescriptorSetLayout &AddLayoutBinding(uint32_t binding, uint32_t count, DescriptorType type, ShaderStage shaderStage);

        const VkDescriptorSetLayout &GetHandle();
        VkDescriptorSetLayoutBinding GetVkLayoutBinding(uint32_t i);
        const DescriptorBinding &GetLayoutBinding(uint32_t i) const;
        uint32_t GetBindingCount() const;

    private:
        void Build();

        std::vector<DescriptorBinding> mBindings;

        VkDescriptorSetLayout mHandle;
    };
}