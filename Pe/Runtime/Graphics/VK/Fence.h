#pragma once
#include <vulkan/vulkan.h>
namespace Pe2::VK
{
    class Fence
    {
    public:
        Fence(VkFenceCreateFlags flags);
        ~Fence();

        const VkFence &GetVKFenceHandle() const;

        void Wait(bool waitAll, uint64_t timeout);
        void Reset();

    private:
        VkFence m_FenceHandle;
    };
}