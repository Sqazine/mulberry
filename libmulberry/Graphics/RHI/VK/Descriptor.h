#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "Defs.h"
#include "Graphics/RHI/Defs.h"

namespace mulberry::vk
{
    class DescriptorSet : public Base
    {
    public:
        DescriptorSet(class DescriptorPool *descPool, class DescriptorSetLayout *descLayout);
        ~DescriptorSet();

        const VkDescriptorSet &GetHandle() const;

        DescriptorSet &WriteBuffer(uint32_t binding, const class Buffer *buffer, uint64_t offset, uint64_t size);
        DescriptorSet &WriteBuffer(uint32_t binding, const class Buffer *buffer);
        DescriptorSet &WriteImage(uint32_t binding, class Texture *texture);
        DescriptorSet &WriteImageArray(uint32_t binding, const std::vector<class Texture *> &imageInfos);

        void Update();

    private:
        std::unordered_map<uint32_t, VkDescriptorBufferInfo> mBufferInfoCache;
        std::unordered_map<uint32_t, VkDescriptorImageInfo> mImageInfoCache;
        std::unordered_map<uint32_t, std::vector<VkDescriptorImageInfo>> mImagesInfoCache;

        class DescriptorPool *mDescriptorPool;
        DescriptorSetLayout *mDescriptorLayout;
        VkDescriptorSet mHandle;
    };

    class DescriptorSetLayout : public Base
    {
    public:
        DescriptorSetLayout();
        virtual ~DescriptorSetLayout();

        const VkDescriptorSetLayout &GetHandle();
        const VkDescriptorSetLayoutBinding &GetLayoutBinding(uint32_t i);
    private:
        friend class DescriptorTable;
        DescriptorSetLayout &AddLayoutBinding(uint32_t binding, uint32_t count, DescriptorType type, ShaderStage shaderStage);


        uint32_t GetBindingCount() const;

        void Build() override;

        std::vector<VkDescriptorSetLayoutBinding> mBindings;
        VkDescriptorSetLayout mHandle;
    };

    class DescriptorPool : public Base
    {
    public:
        DescriptorPool();
        ~DescriptorPool();

        const VkDescriptorPool &GetHandle();
    private:
        friend class DescriptorTable;

        void AddPoolDesc(DescriptorType type, uint32_t count);
        DescriptorSet *AllocateDescriptorSet(DescriptorSetLayout *descLayout);
        std::vector<DescriptorSet *> AllocateDescriptorSets(DescriptorSetLayout *descLayout, uint32_t count);
        
        void Build() override;

        std::vector<std::unique_ptr<DescriptorSet>> mDescriptorSetCache;
        std::unordered_map<DescriptorType, uint32_t> mPoolDescs;
        VkDescriptorPool mHandle;
    };

    class DescriptorTable
    {
    public:
        DescriptorTable();
        ~DescriptorTable();

        DescriptorTable &AddLayoutBinding(uint32_t binding, uint32_t count, DescriptorType type, ShaderStage shaderStage);

        class DescriptorSet *AllocateDescriptorSet();
        std::vector<class DescriptorSet *> AllocateDescriptorSets(uint32_t count);

        class DescriptorSetLayout *GetLayout();
        class DescriptorPool *GetPool();

    private:
        std::unique_ptr<class DescriptorPool> mDescriptorPool;
        std::unique_ptr<class DescriptorSetLayout> mDescriptorLayout;
    };
}