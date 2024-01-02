#pragma once
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include "Device.h"
#include "Object.h"

namespace mulberry::vk
{
    template <typename T>
    class CommandPool : public Object
    {
    public:
        CommandPool(uint32_t queueFamilyIndex)
        {
            VkCommandPoolCreateInfo info{};
            info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            info.pNext = nullptr;
            info.queueFamilyIndex = queueFamilyIndex;
            info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

            vkCreateCommandPool(mDevice.GetHandle(), &info, nullptr, &mHandle);
        }
        ~CommandPool()
        {
            vkDestroyCommandPool(mDevice.GetHandle(), mHandle, nullptr);
        }

        const VkCommandPool &GetHandle() const
        {
            return mHandle;
        }

        std::unique_ptr<T> CreatePrimaryCommandBuffer() const
        {
            return std::move(std::make_unique<T>(VK_COMMAND_BUFFER_LEVEL_PRIMARY));
        }
        std::vector<std::unique_ptr<T>> CreatePrimaryCommandBuffers(uint32_t count) const
        {
            std::vector<std::unique_ptr<T>> result(count);
            for (auto &e : result)
                e = std::move(CreatePrimaryCommandBuffer());
            return std::move(result);
        }

        std::unique_ptr<T> CreateSecondaryCommandBuffer() const
        {
            return std::move(std::make_unique<T>(VK_COMMAND_BUFFER_LEVEL_SECONDARY));
        }
        std::vector<std::unique_ptr<T>> CreateSecondaryCommandBuffers(uint32_t count) const
        {
            std::vector<std::unique_ptr<T>> result(count);
            for (auto &e : result)
                e = std::move(CreateSecondaryCommandBuffer());
            return result;
        }

    private:
        VkCommandPool mHandle;
    };

#define COMMAND_POOL_DECL(name)                                             \
    class name##CommandPool : public CommandPool<class name##CommandBuffer> \
    {                                                                       \
    public:                                                                 \
        name##CommandPool();                                                \
        ~name##CommandPool();                                               \
    };

    COMMAND_POOL_DECL(Raster)
    COMMAND_POOL_DECL(Compute)
    COMMAND_POOL_DECL(Transfer)

}