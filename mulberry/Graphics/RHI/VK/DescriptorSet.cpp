#include "DescriptorSet.h"
#include "Device.h"
#include "DescriptorPool.h"
#include "Texture.h"
#include "Logger.h"

namespace mulberry::vk
{

    DescriptorSet::DescriptorSet(DescriptorPool *descPool, DescriptorSetLayout *descLayout)
        : mHandle(VK_NULL_HANDLE), mDescriptorLayout(descLayout), mDescriptorPool(descPool)
    {
        VkDescriptorSetAllocateInfo descriptorSetAllocInfo = {};
        descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        descriptorSetAllocInfo.pNext = nullptr;
        descriptorSetAllocInfo.pSetLayouts = &mDescriptorLayout->GetHandle();
        descriptorSetAllocInfo.descriptorPool = descPool->GetHandle();
        descriptorSetAllocInfo.descriptorSetCount = 1;

        VK_CHECK(vkAllocateDescriptorSets(mDescriptorPool->GetRelatedDevice().GetHandle(), &descriptorSetAllocInfo, &mHandle));
    }

    DescriptorSet::~DescriptorSet()
    {
        vkFreeDescriptorSets(mDescriptorPool->GetRelatedDevice().GetHandle(), mDescriptorPool->GetHandle(), 1, &mHandle);
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

    DescriptorSet &DescriptorSet::WriteAccelerationStructure(uint32_t binding, const VkAccelerationStructureKHR &as)
    {
        VkWriteDescriptorSetAccelerationStructureKHR structureInfo = {};
        structureInfo.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR;
        structureInfo.pNext = nullptr;
        structureInfo.accelerationStructureCount = 1;
        structureInfo.pAccelerationStructures = &as;

        mASInfoCache[binding] = structureInfo;
        return *this;
    }

    void DescriptorSet::Update()
    {
        std::vector<VkWriteDescriptorSet> writeDescriptorSets;
        for (const auto &bufferInfoCache : mBufferInfoCache)
        {
            auto layoutBinding = mDescriptorLayout->GetVkLayoutBinding(bufferInfoCache.first);

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
            auto layoutBinding = mDescriptorLayout->GetVkLayoutBinding(imageInfoCache.first);

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
            auto layoutBinding = mDescriptorLayout->GetVkLayoutBinding(imagesInfoCache.first);

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

        for (const auto &asInfo : mASInfoCache)
        {
            auto layoutBinding = mDescriptorLayout->GetVkLayoutBinding(asInfo.first);

            VkWriteDescriptorSet setWrite{};
            setWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            setWrite.pNext = &asInfo.second;
            setWrite.dstSet = mHandle;
            setWrite.dstBinding = asInfo.first;
            setWrite.dstArrayElement = 0;
            setWrite.descriptorCount = 1;
            setWrite.descriptorType = layoutBinding.descriptorType;
            setWrite.pBufferInfo = nullptr;
            setWrite.pImageInfo = nullptr;
            setWrite.pTexelBufferView = nullptr;

            writeDescriptorSets.emplace_back(setWrite);
        }

        vkUpdateDescriptorSets(mDescriptorPool->GetRelatedDevice().GetHandle(), writeDescriptorSets.size(), writeDescriptorSets.data(), 0, nullptr);

        mBufferInfoCache.clear();
        mImageInfoCache.clear();
        mImagesInfoCache.clear();
        mASInfoCache.clear();
    }

}