#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VKBuffer.h"

namespace mulberry
{

    template <typename T>
    class VKIndexBuffer : public VKBuffer
    {
    public:
        VKIndexBuffer(const std::vector<T> &indices);
        VkIndexType GetDataType() const;

    private:
        VkIndexType DataStr2VkIndexType(std::string_view dataStr) const;
        VkIndexType mDataType;
    };

    template <typename T>
    inline VKIndexBuffer<T>::VKIndexBuffer(const std::vector<T> &indices)
        : Buffer(sizeof(T) * indices.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
    {
        mDataType = DataStr2VkIndexType(typeid(T).name());

        VkDeviceSize bufferSize = sizeof(T) * indices.size();
        VKBuffer stagingBuffer = VKBuffer(bufferSize,
                                          VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        stagingBuffer.Fill(bufferSize, indices.data());

        Context::GetDevice()->GetGraphicsCommandPool()->SubmitOnce([bufferSize, &stagingBuffer, this](CommandBuffer *cmd)
                                                                   {
                                                                       VkBufferCopy copyRegion{};
                                                                       copyRegion.srcOffset = 0;
                                                                       copyRegion.dstOffset = 0;
                                                                       copyRegion.size = bufferSize;

                                                                       this->CopyFrom(cmd, copyRegion, stagingBuffer);
                                                                   });
    }
    template <typename T>
    inline VkIndexType VKIndexBuffer<T>::GetDataType() const
    {
        return mDataType;
    }

    template <typename T>
    inline VkIndexType VKIndexBuffer<T>::DataStr2VkIndexType(std::string_view dataStr) const
    {
        if (dataStr.compare("uint32_t") == 0 || dataStr.compare("unsigned int") == 0)
            return VK_INDEX_TYPE_UINT32;
        else if (dataStr.compare("uint8_t") == 0 || dataStr.compare("unsigned char") == 0)
            return VK_INDEX_TYPE_UINT8_EXT;
        else if (dataStr.compare("uint16_t") == 0 || dataStr.compare("unsigned short") == 0)
            return VK_INDEX_TYPE_UINT16;
        return VK_INDEX_TYPE_UINT32;
    }
}