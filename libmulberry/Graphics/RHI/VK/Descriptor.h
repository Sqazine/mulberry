#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "Buffer.h"
#include "Base.h"
#include "../Enum.h"

namespace mulberry::rhi::vk
{
    class DescriptorSet : public Base
    {
    public:
        DescriptorSet(class DescriptorPool *descPool, class DescriptorSetLayout *descLayout);
        ~DescriptorSet();

        const VkDescriptorSet &GetHandle() const;

        DescriptorSet &WriteBuffer(uint32_t binding, const Buffer *buffer, uint64_t offset, uint64_t size);
        DescriptorSet &WriteBuffer(uint32_t binding, const Buffer *buffer);
        DescriptorSet &WriteImage(uint32_t binding, class Texture *texture);
        DescriptorSet &WriteImageArray(uint32_t binding, const std::vector<class Texture *> &imageInfos);
        DescriptorSet &WriteAccelerationStructure(uint32_t binding, const VkAccelerationStructureKHR &as);

        void Update();

    private:
        std::unordered_map<uint32_t, VkDescriptorBufferInfo> mBufferInfoCache;
        std::unordered_map<uint32_t, VkDescriptorImageInfo> mImageInfoCache;
        std::unordered_map<uint32_t, std::vector<VkDescriptorImageInfo>> mImagesInfoCache;
        std::unordered_map<uint32_t, VkWriteDescriptorSetAccelerationStructureKHR> mASInfoCache;

        class DescriptorPool *mDescriptorPool;
        DescriptorSetLayout *mDescriptorLayout;
        VkDescriptorSet mHandle;
    };

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
            tmp.stageFlags = ToVkShaderStage(shaderStage);
            tmp.pImmutableSamplers = VK_NULL_HANDLE;
            return tmp;
        }
    };

    class DescriptorSetLayout : public Base
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

    class DescriptorPool : public Base
    {
    public:
        DescriptorPool();
        ~DescriptorPool();

        void AddPoolDesc(DescriptorType type, uint32_t count);

        const VkDescriptorPool &GetHandle();

        DescriptorSet *AllocateDescriptorSet(DescriptorSetLayout *descLayout);
        std::vector<DescriptorSet *> AllocateDescriptorSets(DescriptorSetLayout *descLayout, uint32_t count);

    private:
        void Build();

        std::vector<std::unique_ptr<DescriptorSet>> mDescriptorSetCache;
        std::unordered_map<DescriptorType, uint32_t> mPoolDescs;
        VkDescriptorPool mHandle;
    };

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