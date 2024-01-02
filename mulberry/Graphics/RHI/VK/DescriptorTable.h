#pragma once
#include <memory>
#include <vector>
#include "../Enum.h"

namespace mulberry::vk
{
    class DescriptorTable
    {
    public:
        DescriptorTable();
        ~DescriptorTable();

        DescriptorTable &AddLayoutBinding(const struct DescriptorBinding &binding);
        DescriptorTable &AddLayoutBinding(uint32_t binding, uint32_t count, DescriptorType type, ShaderStage shaderStage);

        class DescriptorSet *AllocateDescriptorSet();
        std::vector<class DescriptorSet *> AllocateDescriptorSets(uint32_t count);

        class DescriptorSetLayout *GetLayout();
        class DescriptorPool *GetPool();

        struct DescriptorBinding GetLayoutBinding(uint32_t i);
        uint32_t GetBindingCount() const;

    private:
        std::unique_ptr<class DescriptorPool> mDescriptorPool;
        std::unique_ptr<class DescriptorSetLayout> mDescriptorLayout;
    };
}