#pragma once
#include <vulkan/vulkan.h>

namespace mulberry::vk
{
    constexpr uint64_t FENCE_WAIT_TIME_OUT = UINT64_MAX;

    class Fence
    {
    public:
        Fence();
        ~Fence();

        const VkFence &GetHandle() const;

        void Wait();
        void Reset();

    private:
        VkFence mHandle;
    };
}