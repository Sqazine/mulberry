#include "Descriptor.h"
#include "Device.h"
#include "Logger.h"
#include "Texture.h"
#include "Buffer.h"
namespace mulberry::vk
{
    DescriptorSetLayout::DescriptorSetLayout()
        : mHandle(VK_NULL_HANDLE)
    {
    }

    DescriptorSetLayout::~DescriptorSetLayout()
    {
        vkDestroyDescriptorSetLayout(mDevice.GetHandle(), mHandle, nullptr);
    }

    DescriptorSetLayout &DescriptorSetLayout::AddLayoutBinding(uint32_t binding, uint32_t count, DescriptorType type, ShaderStage shaderStage)
    {
        VkDescriptorSetLayoutBinding layoutBinding{};
        layoutBinding.binding=binding;
        layoutBinding.descriptorCount=count;
        layoutBinding.descriptorType=DESCRIPTOR_TYPE_CAST(type);
        layoutBinding.stageFlags=ToVkShaderStage(shaderStage);
        mBindings.emplace_back(layoutBinding);
        return *this;
    }

    const VkDescriptorSetLayout &DescriptorSetLayout::GetHandle()
    {
        if (mHandle == VK_NULL_HANDLE)
            Build();
        return mHandle;
    }

    const VkDescriptorSetLayoutBinding &DescriptorSetLayout::GetLayoutBinding(uint32_t i)
    {
        return mBindings[i];
    }

    uint32_t DescriptorSetLayout::GetBindingCount() const
    {
        return mBindings.size();
    }

    void DescriptorSetLayout::Build()
    {
        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
        descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutInfo.pNext = nullptr;
        descriptorSetLayoutInfo.flags = 0;
        descriptorSetLayoutInfo.bindingCount = mBindings.size();
        descriptorSetLayoutInfo.pBindings = mBindings.data();

        VK_CHECK(vkCreateDescriptorSetLayout(mDevice.GetHandle(), &descriptorSetLayoutInfo, nullptr, &mHandle));
    }

    DescriptorSet::DescriptorSet(DescriptorPool *descPool, DescriptorSetLayout *descLayout)
        : mHandle(VK_NULL_HANDLE), mDescriptorLayout(descLayout), mDescriptorPool(descPool)
    {
        VkDescriptorSetAllocateInfo descriptorSetAllocInfo = {};
        descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        descriptorSetAllocInfo.pNext = nullptr;
        descriptorSetAllocInfo.pSetLayouts = &mDescriptorLayout->GetHandle();
        descriptorSetAllocInfo.descriptorPool = descPool->GetHandle();
        descriptorSetAllocInfo.descriptorSetCount = 1;

        VK_CHECK(vkAllocateDescriptorSets(mDescriptorPool->GetDevice().GetHandle(), &descriptorSetAllocInfo, &mHandle));
    }

    DescriptorSet::~DescriptorSet()
    {
        vkFreeDescriptorSets(mDescriptorPool->GetDevice().GetHandle(), mDescriptorPool->GetHandle(), 1, &mHandle);
    }

    const VkDescriptorSet &DescriptorSet::GetHandle() const
    {
        return mHandle;
    }

    DescriptorSet &DescriptorSet::WriteBuffer(uint32_t binding, const Buffer *buffer, uint64_t offset, uint64_t size)
    {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = buffer->GetHandle();
        bufferInfo.offset = offset;
        bufferInfo.range = size;

        mBufferInfoCache[binding] = bufferInfo;

        return *this;
    }

    DescriptorSet &DescriptorSet::WriteBuffer(uint32_t binding, const Buffer *buffer)
    {
        return WriteBuffer(binding, buffer, 0, buffer->GetSize());
    }

    DescriptorSet &DescriptorSet::WriteImage(uint32_t binding, Texture *texture)
    {
        mImageInfoCache[binding] = texture->ToVkDescriptorImageInfo();
        return *this;
    }

    DescriptorSet &DescriptorSet::WriteImageArray(uint32_t binding, const std::vector<Texture *> &imageInfos)
    {
        std::vector<VkDescriptorImageInfo> rawImageInfos;
        for (const auto &imageInfo : imageInfos)
            rawImageInfos.emplace_back(imageInfo->ToVkDescriptorImageInfo());

        mImagesInfoCache[binding] = rawImageInfos;
        return *this;
    }

    void DescriptorSet::Update()
    {
        std::vector<VkWriteDescriptorSet> writeDescriptorSets;
        for (const auto &bufferInfoCache : mBufferInfoCache)
        {
            auto layoutBinding = mDescriptorLayout->GetLayoutBinding(bufferInfoCache.first);

            VkWriteDescriptorSet setWrite{};
            setWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            setWrite.pNext = nullptr;
            setWrite.dstSet = mHandle;
            setWrite.dstBinding = bufferInfoCache.first;
            setWrite.dstArrayElement = 0;
            setWrite.descriptorCount = 1;
            setWrite.descriptorType = layoutBinding.descriptorType;
            setWrite.pImageInfo = nullptr;
            setWrite.pBufferInfo = &bufferInfoCache.second;
            setWrite.pTexelBufferView = nullptr;

            writeDescriptorSets.emplace_back(setWrite);
        }

        for (const auto &imageInfoCache : mImageInfoCache)
        {
            auto layoutBinding = mDescriptorLayout->GetLayoutBinding(imageInfoCache.first);

            VkWriteDescriptorSet setWrite{};
            setWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            setWrite.pNext = nullptr;
            setWrite.dstSet = mHandle;
            setWrite.dstBinding = imageInfoCache.first;
            setWrite.dstArrayElement = 0;
            setWrite.descriptorCount = 1;
            setWrite.descriptorType = layoutBinding.descriptorType;
            setWrite.pBufferInfo = nullptr;
            setWrite.pImageInfo = &imageInfoCache.second;
            setWrite.pTexelBufferView = nullptr;

            writeDescriptorSets.emplace_back(setWrite);
        }

        for (const auto &imagesInfoCache : mImagesInfoCache)
        {
            auto layoutBinding = mDescriptorLayout->GetLayoutBinding(imagesInfoCache.first);

            VkWriteDescriptorSet setWrite{};
            setWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            setWrite.pNext = nullptr;
            setWrite.dstSet = mHandle;
            setWrite.dstBinding = imagesInfoCache.first;
            setWrite.dstArrayElement = 0;
            setWrite.descriptorCount = imagesInfoCache.second.size();
            setWrite.descriptorType = layoutBinding.descriptorType;
            setWrite.pBufferInfo = nullptr;
            setWrite.pImageInfo = imagesInfoCache.second.data();
            setWrite.pTexelBufferView = nullptr;

            writeDescriptorSets.emplace_back(setWrite);
        }

        vkUpdateDescriptorSets(mDescriptorPool->GetDevice().GetHandle(), writeDescriptorSets.size(), writeDescriptorSets.data(), 0, nullptr);

        mBufferInfoCache.clear();
        mImageInfoCache.clear();
        mImagesInfoCache.clear();
    }

    DescriptorPool::DescriptorPool()
        : mHandle(VK_NULL_HANDLE)
    {
    }
    DescriptorPool::~DescriptorPool()
    {
        mDescriptorSetCache.clear();
        vkDestroyDescriptorPool(mDevice.GetHandle(), mHandle, nullptr);
    }

    void DescriptorPool::AddPoolDesc(DescriptorType type, uint32_t count)
    {
        auto iter = mPoolDescs.find(type);
        if (iter != mPoolDescs.end())
            mPoolDescs[type] += count;
        else
            mPoolDescs[type] = count;
    }

    const VkDescriptorPool &DescriptorPool::GetHandle()
    {
        if (mHandle == VK_NULL_HANDLE)
            Build();
        return mHandle;
    }

    DescriptorSet *DescriptorPool::AllocateDescriptorSet(DescriptorSetLayout *descLayout)
    {
        mDescriptorSetCache.emplace_back(std::move(std::make_unique<DescriptorSet>(this, descLayout)));
        return mDescriptorSetCache.back().get();
    }

    std::vector<DescriptorSet *> DescriptorPool::AllocateDescriptorSets(DescriptorSetLayout *descLayout, uint32_t count)
    {
        std::vector<DescriptorSet *> result(count);
        for (int32_t i = 0; i < count; ++i)
            result[i] = AllocateDescriptorSet(descLayout);
        return result;
    }

    void DescriptorPool::Build()
    {
        std::vector<VkDescriptorPoolSize> poolSizes;
        for (const auto &poolDesc : mPoolDescs)
        {
            VkDescriptorPoolSize poolSize{};
            poolSize.type = DESCRIPTOR_TYPE_CAST(poolDesc.first);
            poolSize.descriptorCount = poolDesc.second;
            poolSizes.emplace_back(poolSize);
        }

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.pNext = nullptr;
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        poolInfo.maxSets = 256;
        poolInfo.poolSizeCount = poolSizes.size();
        poolInfo.pPoolSizes = poolSizes.data();

        VK_CHECK(vkCreateDescriptorPool(mDevice.GetHandle(), &poolInfo, nullptr, &mHandle));
    }

    DescriptorTable::DescriptorTable()
        : mDescriptorPool(std::make_unique<DescriptorPool>()), mDescriptorLayout(std::make_unique<DescriptorSetLayout>())
    {
    }

    DescriptorTable::~DescriptorTable()
    {
    }

    DescriptorTable &DescriptorTable::AddLayoutBinding(uint32_t binding, uint32_t count, DescriptorType type, ShaderStage shaderStage)
    {
        mDescriptorPool->AddPoolDesc(type, count);
        mDescriptorLayout->AddLayoutBinding(binding, count, type, shaderStage);
        return *this;
    }

    DescriptorSet *DescriptorTable::AllocateDescriptorSet()
    {
        return mDescriptorPool->AllocateDescriptorSet(mDescriptorLayout.get());
    }

    std::vector<DescriptorSet *> DescriptorTable::AllocateDescriptorSets(uint32_t count)
    {
        return mDescriptorPool->AllocateDescriptorSets(mDescriptorLayout.get(), count);
    }

    DescriptorSetLayout *DescriptorTable::GetLayout()
    {
        return mDescriptorLayout.get();
    }

    DescriptorPool *DescriptorTable::GetPool()
    {
        return mDescriptorPool.get();
    }
}