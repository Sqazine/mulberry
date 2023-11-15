#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VKBuffer.h"

namespace mulberry
{
    class VKIndexBuffer : public VKGpuBuffer
    {
    public:
        VKIndexBuffer();
        template <typename T>
        VKIndexBuffer(const std::vector<T> &indices);
        ~VKIndexBuffer();

        template <typename T>
        void Set(const std::vector<T> &input);

        uint32_t Size() const;

        VkIndexType GetDataType() const;

    private:
        VkIndexType DataStr2VkIndexType(std::string_view dataStr) const;

        uint32_t mSize;
        VkIndexType mDataType;
    };

    inline VKIndexBuffer::VKIndexBuffer()
        : VKGpuBuffer(0, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
    {
    }

    template <typename T>
    inline VKIndexBuffer::VKIndexBuffer(const std::vector<T> &indices)
        : VKGpuBuffer(sizeof(T) * indices.size(), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
    {
        Set(indices);
    }

    inline VKIndexBuffer::~VKIndexBuffer()
    {
    }

    template <typename T>
    inline void VKIndexBuffer::Set(const std::vector<T> &input)
    {
        mSize = input.size();

        mDataType = DataStr2VkIndexType(typeid(T).name());

        VkDeviceSize bufferSize = sizeof(T) * input.size();
        VKCpuBuffer stagingBuffer = VKCpuBuffer(bufferSize,
                                                VK_BUFFER_USAGE_TRANSFER_SRC_BIT);

        stagingBuffer.Fill(bufferSize, input.data());

        CopyFromStagingBuffer(bufferSize, stagingBuffer);
    }

    inline uint32_t VKIndexBuffer::Size() const
    {
        return mSize;
    }

    inline VkIndexType VKIndexBuffer::GetDataType() const
    {
        return mDataType;
    }

    inline VkIndexType VKIndexBuffer::DataStr2VkIndexType(std::string_view dataStr) const
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