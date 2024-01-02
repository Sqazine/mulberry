#pragma once
#include <vulkan/vulkan.h>
#include <unordered_map>
#include <cstdint>
#include "Object.h"
#include "Buffer.h"

namespace mulberry::vk
{

    class DescriptorSet : public Object
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
}